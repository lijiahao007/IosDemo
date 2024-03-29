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
 * AudioOutput 一次只能创建一次
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
@property (nonatomic, assign) AUNode timePitchNode;
@property (nonatomic, assign) AudioUnit ioUnit;
@property (nonatomic, assign) AudioUnit timePitchUnit;
@property (nonatomic, assign) SInt16* outBuffer;
@property (nonatomic, assign) BOOL enableRecord; // 是否启动录音
@property (nonatomic, assign) BOOL enablePlay; // 是否启动播放
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
        
        // PS 至少有一个
        if (_enablePlay || _enableRecord) {
            [self createAudioUnitGraph];
        }
    }
    return self;
}

- (void)dealloc {
    if (_outBuffer) {
        free(_outBuffer);
        _outBuffer = NULL;
    }
    
    [self destroyAudioUnitGraph];
    NSLog(@"AudioOutput dealloc %@", self);
}

- (void)setRate:(Float32)rate {
    if (rate == _rate || !_isInitGraph) { return; }
    _rate = rate;
    
    [self setTimePitchRate];
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


-(void) createAudioUnitGraph {
    OSStatus status = noErr;
    
    status = NewAUGraph(&_progressGraph);
    CheckStatus(status, @"Could not create a new AUGraph", YES);
    
    [self addAudioUnitNodes];

    status = AUGraphOpen(_progressGraph);
    CheckStatus(status, @"Could not open AUGraph", YES);
    
    [self getUnitFromNode];
    [self setUnitScopeEnable];
    [self setAudioUnitProperties];
    
    [self makeNodeConnections];
    
    CAShow(_progressGraph);
    
    status = AUGraphInitialize(_progressGraph);
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
}


-(void) getUnitFromNode {
    OSStatus status = noErr;

    status = AUGraphNodeInfo(_progressGraph, _ioNode, NULL, &_ioUnit);
    CheckStatus(status, @"Could not retrieve node info for I/O node", YES);
    
    status = AUGraphNodeInfo(_progressGraph, _timePitchNode, NULL, &_timePitchUnit);
    CheckStatus(status, @"Could not retrieve node info for TimePitch node", YES);
}

/**
 1.kAudioOutputUnitProperty_EnableIO 的设置只能在 AUGraphInitialize前 设置到对应AudioUnit中
 2. ioUnit 的 outputElement(element0) 的outputScope 是和扬声器连接的； inputElement(element1)的inputScope是和麦克风连接的。
     ioUnit 必须和至少一个硬件连接才可以 AUGraphInitialize 成功。
 */
-(void) setUnitScopeEnable {
    OSStatus status = noErr;
    
    // 启用播放
    UInt32 enablePlay = _enablePlay ? 1 : 0;
    status = AudioUnitSetProperty(_ioUnit, kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Output, outputElement, &enablePlay, sizeof(enablePlay));
    CheckStatus(status, @"Cloud not SetEnable for ioUnit outputElement outputScope", YES);
    
    // 启用录音
    UInt32 enableRecord = _enableRecord ? 1 : 0;
    status = AudioUnitSetProperty(_ioUnit, kAudioOutputUnitProperty_EnableIO, kAudioUnitScope_Input, inputElement, &enableRecord, sizeof(enableRecord));
    CheckStatus(status, @"Cloud not setEnable for io Unit inputElement inputScope", YES);
}


-(void) setAudioUnitProperties {
    OSStatus status = noErr;
    
    AudioStreamBasicDescription description = [self getStreamFormat];
    
    // 输入端输出格式
    status = AudioUnitSetProperty(_ioUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, inputElement, &description, sizeof(description));
    CheckStatus(status, @"Could not set stream format on I/O unit inputElement output scope", YES);

//    
//    status = AudioUnitSetProperty(_timePitchUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Output, outputElement, &description, sizeof(description));
//    CheckStatus(status, @"Could not set stream format on timePitch Unit outputElement output scope", YES);
//    status = AudioUnitSetProperty(_timePitchUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, outputElement, &description, sizeof(description));
//    CheckStatus(status, @"Could not set stream format on timePitch Unit outputElement input scope", YES);
    
}

-(void) makeNodeConnections {
    OSStatus status = noErr;
    
    // 将 （timePitchNode的element0的outputScope） 与 （ioNode的element0的inputScope） 连接在一起。
    status = AUGraphConnectNodeInput(_progressGraph, _timePitchNode, 0, _ioNode, 0);
    CheckStatus(status, @"Could not connect I/O node input to timePitch node input", YES);
    
    AURenderCallbackStruct callbackStruct;
    callbackStruct.inputProc = &InputRenderCallback;
    callbackStruct.inputProcRefCon = (__bridge void *)self;
    status = AudioUnitSetProperty(_timePitchUnit, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input, outputElement, &callbackStruct, sizeof(callbackStruct));
    CheckStatus(status, @"Could not set render callback on timePitch input scope, element 1", YES);

    AURenderCallbackStruct recordCallbackStruct;
    recordCallbackStruct.inputProc = &RecordCallback;
    recordCallbackStruct.inputProcRefCon = (__bridge void *)self;
    status = AudioUnitSetProperty(_ioUnit, kAudioOutputUnitProperty_SetInputCallback, kAudioUnitScope_Output, inputElement, &recordCallbackStruct, sizeof(recordCallbackStruct));
    CheckStatus(status, @"Could not set record callback on io unit output scope, element 1", YES);
}


-(AudioStreamBasicDescription) getStreamFormat {
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


- (void)destroyAudioUnitGraph {
    if (_progressGraph) {
        AUGraphStop(_progressGraph);
        AUGraphUninitialize(_progressGraph);
        AUGraphClose(_progressGraph);
        AUGraphRemoveNode(_progressGraph, _ioNode);
        DisposeAUGraph(_progressGraph);
    }
    _ioUnit = NULL;
    _ioNode = 0;
    _timePitchNode = 0;
    _timePitchUnit = NULL;
    _progressGraph = NULL;
    _isRunning = NO;
    _isInitGraph = NO;
    NSLog(@"AudioOutput destroyAudioUnitGraph");
}


- (void)play {
    if (_isRunning || !_isInitGraph) return;
    
    OSStatus status = AUGraphStart(_progressGraph);
    CheckStatus(status, @"Could not start AUGraph", YES);
    _isRunning = YES;
}

- (void)stop {
    if (!_isRunning || !_isInitGraph) return;
    OSStatus status = AUGraphStop(_progressGraph);
    CheckStatus(status, @"Could not stop AUGraph", YES);
    _isRunning = NO;
}

static void CheckStatus(OSStatus status, NSString *message, BOOL fatal) {
    if(status != noErr)
    {
        char fourCC[16];
        *(UInt32 *)fourCC = CFSwapInt32HostToBig(status);
        fourCC[4] = '\0';
        
        if(isprint(fourCC[0]) && isprint(fourCC[1]) && isprint(fourCC[2]) && isprint(fourCC[3]))
            NSLog(@"%@: %s - 1", message, fourCC);
        else
            NSLog(@"%@: %d - 2", message, (int)status);
        
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
        
        return status;
    }
}


#pragma mark - getter / setter

- (BOOL)isRunning {
    return _isRunning;
}

- (BOOL)enableRecord {
    return _enableRecord;
}

- (BOOL)enablePlay {
    return _enablePlay;
}


@end
