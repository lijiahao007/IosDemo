//
//  AudioPlayer.m
//  NVSDK
//
//  Created by package on 2024/3/27.
//  Copyright © 2024 macrovideo. All rights reserved.

/**
 *      Setup AudioSession
 * 1: Category
 * 2: Set Listener
 *      Interrupt Listener
 *      AudioRoute Change Listener
 *      Hardwate output Volume Listener
 * 3: Set IO BufferDuration
 * 4: Active AudioSession
 *
 *      Setup AudioUnit
 * 1:Build AudioComponentDescription To Build AudioUnit Instance
 * 2:Build AudioStreamBasicDescription To Set AudioUnit Property
 * 3:Connect Node Or Set RenderCallback For AudioUnit
 * 4:Initialize AudioUnit
 * 5:Initialize AudioUnit
 * 6:AudioOutputUnitStart
 *
 改变graph流程 ：stop graph（must）-> edit graph(remove/add/connect/disconnect node..., update to be changed) -> graph update（graph changed）->start graph(optional)
 改变property： stop graph（must）-> change property ->start graph(optional)
         如果是涉及到内存分配的property，例如kAudioOutputUnitProperty_EnableIO， 则是需要以下流程：  stop graph (must) -> uninit graph (must) -> change property -> init graph (must) -> start graph (optional)
 改变pramater：change pramater
 *
 **/


#import "AudioOutput.h"
#import "FIFORingQueueManager.h"
#import <AVFoundation/AVFoundation.h>

#define OUTPUT_BUFFER_SIZE 1024*1024 // 1Mb

static const AudioUnitElement inputElement = 1; // 控制输入端 （element1）
static const AudioUnitElement outputElement = 0; // 控制输出端 （element0）

static void CheckStatus(OSStatus status, NSString *message, BOOL fatal);

static OSStatus InputRenderCallback(void *inRefCon,
                                    AudioUnitRenderActionFlags *ioActionFlags,
                                    const AudioTimeStamp *inTimeStamp,
                                    UInt32 inBusNumber,
                                    UInt32 inNumberFrames,
                                    AudioBufferList *ioData);

static OSStatus RecordCallback(void *inRefCon,
                                    AudioUnitRenderActionFlags *ioActionFlags,
                                    const AudioTimeStamp *inTimeStamp,
                                    UInt32 inBusNumber,
                                    UInt32 inNumberFrames,
                                    AudioBufferList *ioData);

@interface AudioOutput()
@property (nonatomic, assign) AUGraph progressGraph;
@property (nonatomic, assign) AUNode ioNode;
@property (nonatomic, assign) AUNode C32f_16iConvertNode;
@property (nonatomic, assign) AUNode timePitchNode;
@property (nonatomic, assign) AUNode C16i_32fConvertNode;
@property (nonatomic, assign) AUNode dynamicsProcessNode; // 音量的增益

@property (nonatomic, assign) AudioUnit ioUnit;
@property (nonatomic, assign) AudioUnit C32f_16iConvertUnit;
@property (nonatomic, assign) AudioUnit timePitchUnit;
@property (nonatomic, assign) AudioUnit C16i_32fConvertUnit;

/**
 作用：截断超过kDynamicsProcessorParam_HeadRoom的音频数据。压缩低于kDynamicsProcessorParam_Threshold的音频信号（表现就是减少低于阈值的声音，用于减少背景噪声的影响）。
        `kDynamicsProcessorParam_OverallGain`: 音量增益（主要用了这部分的功能）
        `kDynamicsProcessorParam_MasterGain`: 音量增益 （已被弃用）
        `kDynamicsProcessorParam_ExpansionRatio`：低于阈值时的压缩比率。比率越大，则压缩后的音频信号越弱
        `kDynamicsProcessorParam_AttackTime`：设置压缩器的起音时间，控制响应速度。
        `kDynamicsProcessorParam_ReleaseTime`：设置压缩器的释音时间，控制响应平滑度。
 */
@property (nonatomic, assign) AudioUnit dynamicsProcessUnit;

@property (nonatomic, assign) SInt16* outBuffer;
@property (nonatomic, assign) int sampleRate;
@property (nonatomic, assign) BOOL isRunning;
@property (nonatomic, assign) BOOL isInitGraph; // 是否初始化的Graph

@end

@implementation AudioOutput

- (instancetype)initWithSampleRate:(int)sampleRate enableRecord:(BOOL)enableRecord enablePlay:(BOOL)enablePlay rate:(float)rate{
    self = [super init];
    if (self) {
        NSLog(@"AudioOutput init %@", self);
        _outBuffer = (SInt16*) malloc(OUTPUT_BUFFER_SIZE);
        _enableRecord = enableRecord;
        _enablePlay = enablePlay;
        _sampleRate = sampleRate;
        _rate = rate;
        _isRunning = NO;
        
        // PS：至少要播放或者录制。如果两个都没有，就没有必要创建AuGraph了。
        if (_enablePlay || _enableRecord) {
            [self createAudioUnitGraph];
        }
        
//        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(changeRate:) name:@"changeRate" object:nil];
    }
    return self;
}

-(void) changeRate:(NSNotification*)nofity {
    float rate = [nofity.userInfo[@"rate"] floatValue];
    self.rate = rate;
}

- (void)dealloc {
    if (_outBuffer) {
        free(_outBuffer);
        _outBuffer = NULL;
    }
    
    [self destroyAudioUnitGraph];
    NSLog(@"AudioOutput dealloc %@", self);
    
//    [[NSNotificationCenter defaultCenter] removeObserver:self name:@"changeRate" object:nil];
}


-(void) createAudioUnitGraph {
    OSStatus status = noErr;
    
    status = NewAUGraph(&_progressGraph);
    CheckStatus(status, @"Could not create a new AUGraph", YES);
    
    [self addAudioUnitNodes];

    [self openAUGraph];
    
    [self getUnitFromNode];
    [self setUnitScopeEnable];
    [self setTimePitchRate];
    [self setAudioUnitProperties];
    
    [self makeNodeConnections];
    
    CAShow(_progressGraph);
    
    [self initializeAUGraph];
    CheckStatus(status, @"Could not initialize AUGraph", YES);
    
    _isInitGraph = YES;
}

-(void) addAudioUnitNodes {
    OSStatus status = noErr;

    // 1. 创建需要AudioUnit的描述
    AudioComponentDescription ioDescription;
    ioDescription.componentType = kAudioUnitType_Output;
    ioDescription.componentSubType = kAudioUnitSubType_VoiceProcessingIO;
    ioDescription.componentManufacturer = kAudioUnitManufacturer_Apple;
    ioDescription.componentFlags = 0;
    ioDescription.componentFlagsMask = 0;
    status = AUGraphAddNode(_progressGraph, &ioDescription, &_ioNode);
    CheckStatus(status, @"Could not add I/O node to AUGraph", YES);

    AudioComponentDescription timePitchDescription;
    timePitchDescription.componentType = kAudioUnitType_FormatConverter;
    timePitchDescription.componentSubType = kAudioUnitSubType_NewTimePitch;
    timePitchDescription.componentManufacturer = kAudioUnitManufacturer_Apple;
    timePitchDescription.componentFlags = 0;
    timePitchDescription.componentFlagsMask = 0;
    status = AUGraphAddNode(_progressGraph, &timePitchDescription, &_timePitchNode);
    CheckStatus(status, @"Could not add TimePitch node to AUGraph", YES);
    
    
    AudioComponentDescription c16i_32fDes;
    c16i_32fDes.componentType = kAudioUnitType_FormatConverter;
    c16i_32fDes.componentSubType = kAudioUnitSubType_AUConverter;
    c16i_32fDes.componentManufacturer = kAudioUnitManufacturer_Apple;
    c16i_32fDes.componentFlags = 0;
    c16i_32fDes.componentFlagsMask = 0;
    status = AUGraphAddNode(_progressGraph, &c16i_32fDes, &_C16i_32fConvertNode);
    CheckStatus(status, @"Could not add _C16i_32fConvertNode to AUGraph", YES);
    
    AudioComponentDescription c32f_16iDes;
    c32f_16iDes.componentType = kAudioUnitType_FormatConverter;
    c32f_16iDes.componentSubType = kAudioUnitSubType_AUConverter;
    c32f_16iDes.componentManufacturer = kAudioUnitManufacturer_Apple;
    c32f_16iDes.componentFlags = 0;
    c32f_16iDes.componentFlagsMask = 0;
    status = AUGraphAddNode(_progressGraph, &c32f_16iDes, &_C32f_16iConvertNode);
    CheckStatus(status, @"Could not add _C32f_16iConvertNode to AUGraph", YES);
    
    
    AudioComponentDescription dynamicsProcessDes;
    dynamicsProcessDes.componentType = kAudioUnitType_Effect;
    dynamicsProcessDes.componentSubType = kAudioUnitSubType_DynamicsProcessor;
    dynamicsProcessDes.componentManufacturer = kAudioUnitManufacturer_Apple;
    dynamicsProcessDes.componentFlags = 0;
    dynamicsProcessDes.componentFlagsMask = 0;
    status = AUGraphAddNode(_progressGraph, &dynamicsProcessDes, &_dynamicsProcessNode);
    CheckStatus(status, @"Could not add _C32f_16iConvertNode to AUGraph", YES);
    
}


-(void) getUnitFromNode {
    OSStatus status = noErr;

    status = AUGraphNodeInfo(_progressGraph, _ioNode, NULL, &_ioUnit);
    CheckStatus(status, @"Could not retrieve node info for I/O node", YES);
    
    status = AUGraphNodeInfo(_progressGraph, _timePitchNode, NULL, &_timePitchUnit);
    CheckStatus(status, @"Could not retrieve node info for TimePitch node", YES);
    
    status = AUGraphNodeInfo(_progressGraph, _C16i_32fConvertNode, NULL, &_C16i_32fConvertUnit);
    CheckStatus(status, @"Could not retrieve node info for _C16i_32fConvertNode node", YES);
    
    status = AUGraphNodeInfo(_progressGraph, _C32f_16iConvertNode, NULL, &_C32f_16iConvertUnit);
    CheckStatus(status, @"Could not retrieve node info for _C32f_16iConvertNode node", YES);
    
    status = AUGraphNodeInfo(_progressGraph, _dynamicsProcessNode, NULL, &_dynamicsProcessUnit);
    CheckStatus(status, @"Could not retrieve node info for _dynamicsProcessNode node", YES);
}

/**
 1.kAudioOutputUnitProperty_EnableIO 的设置只能在 AUGraphInitialize前 设置到对应AudioUnit中
 2. ioUnit 的 outputElement(element0) 的outputScope 是和扬声器连接的； inputElement(element1)的inputScope是和麦克风连接的。
     ioUnit 必须和至少一个硬件连接才可以 AUGraphInitialize 成功。
 */
-(void) setUnitScopeEnable {
    OSStatus status = noErr;
    
    // 连接扬声器
    UInt32 enablePlay = _enablePlay ? 1 : 0;
    status = AudioUnitSetProperty(_ioUnit, kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Output, outputElement, &enablePlay, sizeof(enablePlay));
    CheckStatus(status, @"Cloud not SetEnable for ioUnit outputElement outputScope", YES);
    
    // 连接麦克风
    UInt32 enableRecord = _enableRecord ? 1 : 0;
    status = AudioUnitSetProperty(_ioUnit, kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Input, inputElement, &enableRecord, sizeof(enableRecord));
    CheckStatus(status, @"Cloud not setEnable for io Unit inputElement inputScope", YES);
}


-(void) setAudioUnitProperties {
    OSStatus status = noErr;
    
    AudioStreamBasicDescription description16i = [self get16intStreamFormat];
    AudioStreamBasicDescription description32f = [self get32floatStreamFormat];
    AudioStreamBasicDescription description32i = [self get32intStreamFormat];
    
    // 输入端输出格式
    status = AudioUnitSetProperty(_ioUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, inputElement, &description16i, sizeof(description16i));
    CheckStatus(status, @"Could not set stream format on I/O unit inputElement output scope", YES);
    status = AudioUnitSetProperty(_ioUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, outputElement, &description16i, sizeof(description16i));
    CheckStatus(status, @"Could not set stream format on I/O unit outputElement input Scope", YES);
    
    status = AudioUnitSetProperty(_timePitchUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, outputElement, &description32f, sizeof(description32f));
    CheckStatus(status, @"Could not set stream format on _timePitchUnit outputElement output Scope", YES);
    
    status = AudioUnitSetProperty(_timePitchUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, outputElement, &description32f, sizeof(description32f));
    CheckStatus(status, @"Could not set stream format on _timePitchUnit outputElement input Scope", YES);
    
    
    status = AudioUnitSetProperty(_C16i_32fConvertUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, outputElement, &description16i, sizeof(description16i));
    CheckStatus(status, @"Could not set stream format on _C16i_32fConvertUnit outputElement input Scope", YES);
    
    status = AudioUnitSetProperty(_C16i_32fConvertUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, outputElement, &description32f, sizeof(description32f));
    CheckStatus(status, @"Could not set stream format on _C16i_32fConvertUnit outputElement output Scope", YES);
    
    
    status = AudioUnitSetProperty(_C32f_16iConvertUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, outputElement, &description32f, sizeof(description32f));
    CheckStatus(status, @"Could not set stream format on _C32f_16iConvertUnit outputElement intput Scope", YES);
    
    status = AudioUnitSetProperty(_C32f_16iConvertUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, outputElement, &description16i, sizeof(description16i));
    CheckStatus(status, @"Could not set stream format on _C32f_16iConvertUnit outputElement output Scope", YES);
    
    
    // 压缩效果器
    status = AudioUnitSetProperty(_dynamicsProcessUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, outputElement, &description32f, sizeof(description32f));
    CheckStatus(status, @"Could not set stream format on _C32f_16iConvertUnit outputElement intput Scope", YES);
    status = AudioUnitSetProperty(_dynamicsProcessUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, outputElement, &description32f, sizeof(description32f));
    CheckStatus(status, @"Could not set stream format on _C32f_16iConvertUnit outputElement output Scope", YES);
    
}

- (void)setOverallGain:(float)overallGain {
    if (overallGain > 40.0) {
        overallGain = 40.0;
    } else if (overallGain < -40.0) {
        overallGain = -40.0;
    }
    
    if (_overallGain == overallGain || !_isInitGraph) return;
    _overallGain = overallGain;
    
    OSStatus status;
    status = AudioUnitSetParameter(_dynamicsProcessUnit, kDynamicsProcessorParam_OverallGain, kAudioUnitScope_Global, outputElement, overallGain, 0);
    CheckStatus(status, @"Could not set gain on _dynamicsProcessUnit outputElement global Scope", YES);
}

-(AudioStreamBasicDescription) checkStreamForamt:(AudioUnit) unit {
    AudioStreamBasicDescription timepitchDefaultDescription;
    UInt32 descriptionSize = sizeof(timepitchDefaultDescription);
    AudioUnitGetProperty(unit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, outputElement, &timepitchDefaultDescription, &descriptionSize);
    return timepitchDefaultDescription;
}

/**
 监听数据回调(Int16) --> C16i_32fConvert -> timePitch  -> C32f_16iConvert -> ioUnit
 C16i_32fConvert ： 一个转换器，将监听数据 Int16格式的音频转换成 Float32格式的音频
 timePitch ：变速、变调的Unit，这里只用到了变速功能。该Unit只能设置Float32格式的输入输出。因此才会有那两个格式转换器
 C32f_16iConvert： 格式转换器，将TimePitch Unit输出的音频数据由 Float32 转化为 Int16。
 ioUnit:  用来录音和播放音乐的Unit
 */
-(void) makeNodeConnections {
    OSStatus status = noErr;
    status = AUGraphConnectNodeInput(_progressGraph, _C16i_32fConvertNode, 0, _dynamicsProcessNode, 0);
    CheckStatus(status, @"Could not connect _C16i_32fConvertNode node input to _timePitchNode node input", YES);
    status = AUGraphConnectNodeInput(_progressGraph, _dynamicsProcessNode, 0, _timePitchNode, 0);
    CheckStatus(status, @"Could not connect _C16i_32fConvertNode node input to _timePitchNode node input", YES);
    status = AUGraphConnectNodeInput(_progressGraph, _timePitchNode, 0, _C32f_16iConvertNode, 0);
    CheckStatus(status, @"Could not connect _timePitchNode node input to _C32f_16iConvertNode node input", YES);
    status = AUGraphConnectNodeInput(_progressGraph, _C32f_16iConvertNode, 0, _ioNode, 0);
    CheckStatus(status, @"Could not connect _C32f_16iConvertNode node input to _ioNode node input", YES);
    
    
    AURenderCallbackStruct callbackStruct;
    callbackStruct.inputProc = &InputRenderCallback;
    callbackStruct.inputProcRefCon = (__bridge void *)self;
    status = AudioUnitSetProperty(_C16i_32fConvertUnit, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input, outputElement, &callbackStruct, sizeof(callbackStruct));
    CheckStatus(status, @"Could not set render callback on timePitch input scope, element 0", YES);

    AURenderCallbackStruct recordCallbackStruct;
    recordCallbackStruct.inputProc = &RecordCallback;
    recordCallbackStruct.inputProcRefCon = (__bridge void *)self;
    status = AudioUnitSetProperty(_ioUnit, kAudioOutputUnitProperty_SetInputCallback, kAudioUnitScope_Output, inputElement, &recordCallbackStruct, sizeof(recordCallbackStruct));
    CheckStatus(status, @"Could not set record callback on io unit output scope, element 1", YES);
}


-(AudioStreamBasicDescription) get16intStreamFormat {
    AudioStreamBasicDescription streamDescription;
    streamDescription.mSampleRate = _sampleRate;
    streamDescription.mFormatID = kAudioFormatLinearPCM;
    streamDescription.mFormatFlags = kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;
    streamDescription.mBitsPerChannel = 16;  //每个采样点16bit量化
    streamDescription.mBytesPerFrame = 2;
    streamDescription.mChannelsPerFrame = 1;  //单声道
    streamDescription.mBytesPerPacket = streamDescription.mBytesPerFrame *streamDescription.mChannelsPerFrame;
    streamDescription.mFramesPerPacket = 1;
    streamDescription.mReserved = 0;
    return streamDescription;
}

-(AudioStreamBasicDescription) get32intStreamFormat {
    AudioStreamBasicDescription streamDescription;
    streamDescription.mSampleRate = _sampleRate;
    streamDescription.mFormatID = kAudioFormatLinearPCM;
    streamDescription.mFormatFlags = kAudioFormatFlagsAudioUnitCanonical | kAudioFormatFlagIsNonInterleaved;
    streamDescription.mBitsPerChannel = 32;
    streamDescription.mBytesPerFrame = 4;
    streamDescription.mChannelsPerFrame = 1;
    streamDescription.mBytesPerPacket = 32;
    streamDescription.mFramesPerPacket = 1;
    streamDescription.mReserved = 0;
    return streamDescription;
}



-(AudioStreamBasicDescription) get32floatStreamFormat {
    AudioStreamBasicDescription streamDescription;
    UInt32 bytesPerSample = sizeof (AudioUnitSampleType);
    streamDescription.mSampleRate        = _sampleRate;
    streamDescription.mFormatID          = kAudioFormatLinearPCM;
    streamDescription.mFormatFlags       = kAudioFormatFlagsNativeFloatPacked | kAudioFormatFlagIsNonInterleaved;
    streamDescription.mBitsPerChannel    = 8 * bytesPerSample;
    streamDescription.mBytesPerFrame     = bytesPerSample;
    streamDescription.mChannelsPerFrame  = 1;
    streamDescription.mBytesPerPacket    = bytesPerSample;
    streamDescription.mFramesPerPacket   = 1;
    streamDescription.mReserved = 0;
    return streamDescription;
}
 
- (void)destroyAudioUnitGraph {
    if (_progressGraph) {
        [self stopAUGraph];
        [self uninitializeAUGraph];
        [self closeAUGraph];
        [self disposeAuGraph];
    }
    _ioNode = 0;
    _timePitchNode = 0;
    _C16i_32fConvertNode = 0;
    _C32f_16iConvertNode = 0;
    
    _ioUnit = NULL;
    _timePitchUnit = NULL;
    _C16i_32fConvertUnit = NULL;
    _C32f_16iConvertUnit = NULL;
    
    _progressGraph = NULL;
    _isRunning = NO;
    _isInitGraph = NO;
    NSLog(@"AudioOutput destroyAudioUnitGraph");
}


- (void)play {
    if (_isRunning || !_isInitGraph) return;
    
    [self startAuGraph];
    _isRunning = YES;
}

- (void)stop {
    if (!_isRunning || !_isInitGraph) return;
    [self stopAUGraph];
    _isRunning = NO;
}

static void CheckStatus(OSStatus status, NSString *message, BOOL fatal) {
    if(status != noErr)
    {
        char fourCC[16];
        *(UInt32 *)fourCC = CFSwapInt32HostToBig(status);
        fourCC[4] = '\0';
        
        if(isprint(fourCC[0]) && isprint(fourCC[1]) && isprint(fourCC[2]) && isprint(fourCC[3])) {
            NSLog(@"AudioOutput %@: %s - 1", message, fourCC);
        } else {
            NSLog(@"AudioOutput %@: %d - 2", message, (int)status);
        }
        if(fatal)
            exit(-1);
    }
}

/**
 将监听数据设置到TimePitchUnit  outputElement的InputScope中
 */
static OSStatus InputRenderCallback(void *inRefCon,
                                    AudioUnitRenderActionFlags *ioActionFlags,
                                    const AudioTimeStamp *inTimeStamp,
                                    UInt32 inBusNumber,
                                    UInt32 inNumberFrames,
                                    AudioBufferList *ioData) {
    AudioOutput *player = (__bridge AudioOutput*)inRefCon;
    return [player renderData:ioData
                  atTimeStamp:inTimeStamp
                   forElement:inBusNumber
                 numberFrames:inNumberFrames
                        flags:ioActionFlags];
}

- (OSStatus)renderData:(AudioBufferList *)ioData
           atTimeStamp:(const AudioTimeStamp *)timeStamp
            forElement:(UInt32)element
          numberFrames:(UInt32)numFrames
                 flags:(AudioUnitRenderActionFlags *)flags {
    @autoreleasepool {
        for (int iBuffer=0; iBuffer < ioData->mNumberBuffers; ++iBuffer) {
            memset(ioData->mBuffers[iBuffer].mData, 0, ioData->mBuffers[iBuffer].mDataByteSize);
        }
        if(_delegate) {
            [_delegate requestAudioFrame:_outBuffer numFrames:numFrames];
            // ps: 一个frame 2 byte
            for (int iBuffer=0; iBuffer < ioData->mNumberBuffers; ++iBuffer) {
                memcpy((SInt16 *)ioData->mBuffers[iBuffer].mData, _outBuffer, ioData->mBuffers[iBuffer].mDataByteSize);
            }
        }
        return noErr;
    }
}


/**
 获取IOUint inputElement的outputScope输出的麦克风录音数据
 */
static OSStatus RecordCallback(void *inRefCon,
                                    AudioUnitRenderActionFlags *ioActionFlags,
                                    const AudioTimeStamp *inTimeStamp,
                                    UInt32 inBusNumber,
                                    UInt32 inNumberFrames,
                                    AudioBufferList *ioData) {
    AudioOutput *player = (__bridge AudioOutput*)inRefCon;
    return [player recordData:ioData atTimeStamp:inTimeStamp forElement:inBusNumber numberFrames:inNumberFrames flags:ioActionFlags];
}

- (OSStatus)recordData:(AudioBufferList *)ioData
           atTimeStamp:(const AudioTimeStamp *)timeStamp
            forElement:(UInt32)element
          numberFrames:(UInt32)numFrames
                 flags:(AudioUnitRenderActionFlags *)flags {
    @autoreleasepool {
        OSStatus status = noErr;

        AudioBuffer buffer;
        buffer.mDataByteSize = numFrames * 2; // sample size
        buffer.mNumberChannels = 1; // one channel
        buffer.mData = malloc( numFrames * 2 ); // buffer size
        
        // we put our buffer into a bufferlist array for rendering
        AudioBufferList bufferList;
        bufferList.mNumberBuffers = 1;
        bufferList.mBuffers[0] = buffer;
        
        status = AudioUnitRender(_ioUnit,
                                 flags,
                                 timeStamp,
                                 element,
                                 numFrames,
                                 &bufferList);
        
        if (_delegate && [_delegate respondsToSelector:@selector(getRecordData:byteSize:)]) {
            SInt8* buffer = bufferList.mBuffers[0].mData;
            UInt32 dataSize = bufferList.mBuffers[0].mDataByteSize;
            [_delegate getRecordData:buffer byteSize:dataSize];
        }
        
        
        if (bufferList.mBuffers[0].mData != NULL) {
            free(bufferList.mBuffers[0].mData);  // add by yang 出现过一次闪退
        }
        return status;
    }
}


#pragma mark - getter / setter

- (BOOL)isRunning {
    return _isRunning;
}

- (void)setRate:(Float32)rate {
    if (rate == _rate || !_isInitGraph) { return; }
    _rate = rate;
    
    [self setTimePitchRate];
}


- (void)setEnablePlay:(BOOL)enablePlay {
    if (_enablePlay == enablePlay) return;
    
    _enablePlay = enablePlay;
    
    OSStatus status;
    if (_isRunning) {
        [self stopAUGraph];
    }
    
    if (_isInitGraph) {
        [self uninitializeAUGraph];
    }
 

    if (_enablePlay || _enableRecord) {
        if (!_isInitGraph) {
            [self createAudioUnitGraph];
        } else {
            [self setUnitScopeEnable];
            [self initializeAUGraph];
            _isInitGraph = YES;
        }
       
        if (_isRunning) {
            [self startAuGraph];
        }
    }
}

- (void)setEnableRecord:(BOOL)enableRecord {
    if (_enableRecord == enableRecord) return;
    
    _enableRecord = enableRecord;
    OSStatus status;
    
    if (_isRunning) {
        [self stopAUGraph];
    }
    
    if (_isInitGraph) {
        [self uninitializeAUGraph];
    }

    if (_enablePlay || _enableRecord) {
        if (!_isInitGraph) {
            [self createAudioUnitGraph];
        } else {
            [self setUnitScopeEnable];
            [self initializeAUGraph];
        }
       
        if (_isRunning) {
            [self startAuGraph];
        }
    }
}

-(void) setTimePitchRate {
    OSStatus status = noErr;
    status = AudioUnitSetParameter(_timePitchUnit,
                                   kNewTimePitchParam_Rate,
                                   kAudioUnitScope_Global,
                                   0,
                                   _rate,
                                   0);
    CheckStatus(status, @"Cloud not set time pitch unit rate", YES);
}


#pragma mark - AuGraph 操作

- (void)initializeAUGraph {
    if(_progressGraph) {
        OSStatus status;
        Boolean graphIsInitialized;
        status = AUGraphIsInitialized(_progressGraph, &graphIsInitialized);
        CheckStatus(status, @"get graph initialize state error", YES);
        if (!graphIsInitialized) {
            status = AUGraphInitialize(_progressGraph);
            CheckStatus(status, @"graph initialize error", YES);
        }
    }
}


- (void)uninitializeAUGraph {
    if (_progressGraph) {
        OSStatus status;
        Boolean graphIsInitialized;
        status = AUGraphIsInitialized(_progressGraph, &graphIsInitialized);
        CheckStatus(status, @"get graph initialize state error", YES);
        if (graphIsInitialized) {
            status = AUGraphUninitialize(_progressGraph);
            CheckStatus(status, @"uninitialize graph error", YES);
        }
    }
}


-(void) startAuGraph {
    if (_progressGraph) {
        Boolean graphIsRunning;
        OSStatus status;
        status = AUGraphIsRunning(_progressGraph, &graphIsRunning);
        CheckStatus(status, @"get graph running state error", YES);
        if (!graphIsRunning) {
            status = AUGraphStart(_progressGraph);
            CheckStatus(status, @"start graph error", YES);
        }
    }
}

- (void)stopAUGraph {
    if (_progressGraph) {
        OSStatus status;
        Boolean graphIsRunning;
        status = AUGraphIsRunning(_progressGraph, &graphIsRunning);
        CheckStatus(status, @"get graph running state error", YES);
        if (graphIsRunning) {
            status = AUGraphStop(_progressGraph);
            CheckStatus(status, @"stop graph error", YES);
        }
    }
}

-(void) openAUGraph {
    if (_progressGraph) {
        Boolean graphIsOpen;
        OSStatus status;
        status = AUGraphIsOpen(_progressGraph, &graphIsOpen);
        CheckStatus(status, @"get graph open state error", YES);
        if (!graphIsOpen) {
            status = AUGraphOpen(_progressGraph);
            CheckStatus(status, @"open graph error", YES);
        }
    }
}

- (void)closeAUGraph {
    if (_progressGraph) {
        Boolean graphIsOpen;
        OSStatus status;
        status = AUGraphIsOpen(_progressGraph, &graphIsOpen);
        CheckStatus(status, @"get graph open state error", YES);
        
        if (graphIsOpen){
            status = AUGraphClose(_progressGraph);
            CheckStatus(status, @"close graph error", YES);
        }
    }
}

-(void) disposeAuGraph {
    if (_progressGraph) {
        OSStatus status;
        status = DisposeAUGraph(_progressGraph);
        CheckStatus(status, @"deallocates graph error", YES);
    }
}

@end
