////
////  AudioManager.m
////  MyApplication
////
////  Created by 李嘉浩 on 2023/12/25.
////
//
//#import "AudioManager.h"
//#import <AVFoundation/AVFoundation.h>
//
//@interface AudioManager()
//@property (nonatomic, strong) AVAudioSessionCategory prevCategory;
//@property (nonatomic, strong) AVAudioSessionMode prevMode;
//@property (nonatomic, assign) AVAudioSessionCategoryOptions prevOptions;
//
//@property (nonatomic, assign) double sampleRate;
//@property (nonatomic, assign) int channelNumber;
//
//
//@property (nonatomic, assign) AudioUnit ioUnitInstance1;
//
//@end
//
//@implementation AudioManager
//
//- (instancetype)init
//{
//    self = [super init];
//    if (self) {
//        _sampleRate = 44100.0; // 44.1kHz
//        _channelNumber = 1;
//    }
//    return self;
//}
//
//-(void) createAudioUnit {
//    AudioComponentDescription ioUnitDescription;
//    ioUnitDescription.componentType = kAudioUnitType_Output;
//    ioUnitDescription.componentSubType = kAudioUnitSubType_RemoteIO;
//    ioUnitDescription.componentManufacturer = kAudioUnitManufacturer_Apple;
//    ioUnitDescription.componentFlags = 0;
//    ioUnitDescription.componentFlagsMask = 0;
//    
//    AudioComponent ioUnitRef = AudioComponentFindNext(NULL, &ioUnitDescription);
//    AudioComponentInstanceNew(ioUnitRef, &_ioUnitInstance1);
//    
//    OSStatus status;
//    UInt32 enableFlag = 1;
//    UInt32 disableFlag = 0;
//    
//    UInt32 outputElement = 0;
//    UInt32 inputElement = 1;
//    
//    status = AudioUnitSetProperty(_ioUnitInstance1,
//                                  kAudioOutputUnitProperty_EnableIO,
//                                  kAudioUnitScope_Output,
//                                  outputElement,
//                                  &enableFlag,
//                                  sizeof(UInt32));
//    CheckStatus(status, @"enableIO link outputElement outputScope to Speaker ", YES);
//    
//    status = AudioUnitSetProperty(_ioUnitInstance1,
//                                  kAudioOutputUnitProperty_EnableIO,
//                                  kAudioUnitScope_Input,
//                                  inputElement,
//                                  &enableFlag,
//                                  sizeof(UInt32));
//    CheckStatus(status, @"enableIO link inputElement inputScope to Microphone", YES);
//    
//    
//    UInt32 bytesPerSample = sizeof(Float32);
//    AudioStreamBasicDescription streamDescription;
//    memset(&streamDescription, 0, sizeof(AudioStreamBasicDescription));
//    streamDescription.mFormatID = kAudioFormatLinearPCM;
//    streamDescription.mSampleRate = _sampleRate;
//    streamDescription.mChannelsPerFrame = _channelNumber;
//    streamDescription.mFramesPerPacket = 1;
//
//    /**
//     * kAudioFormatFlagsNativeFloatPacked：每个sample都是float格式的
//     * kAudioFormatFlagIsNonInterleaved：非交错的，左声道会存储在AudioBufferList.mBuffers[0]，右声道会存储在AudioBufferList.mBuffers[1]
//     */
//    streamDescription.mFormatFlags = kAudioFormatFlagsNativeFloatPacked | kAudioFormatFlagIsNonInterleaved;
//    streamDescription.mBitsPerChannel = 8 * bytesPerSample;
//    streamDescription.mBytesPerFrame = bytesPerSample;
//    streamDescription.mBytesPerPacket = bytesPerSample;
//    
//
//    status = AudioUnitSetProperty(_ioUnitInstance1,
//                         kAudioUnitProperty_StreamFormat,
//                         kAudioUnitScope_Output,
//                         inputElement,
//                         &streamDescription,
//                         sizeof(AudioStreamBasicDescription));
//    CheckStatus(status, @"setStreamFormat Microphone -> inputElement(OutputScope)", YES);
//    
//    
//    status = AudioUnitSetProperty(_ioUnitInstance1,
//                         kAudioUnitProperty_StreamFormat,
//                         kAudioUnitScope_Input,
//                         outputElement,
//                         &streamDescription,
//                         sizeof(AudioStreamBasicDescription));
//    CheckStatus(status, @"setStreamFormat outputElement(InputScope) -> Speaker", YES);
//    
//    
//    
//    AURenderCallbackStruct renderProc;
//    renderProc.inputProc = renderCallback;
//    renderProc.inputProcRefCon = (__bridge void*)self;
//    status = AudioUnitSetProperty(_ioUnitInstance1,
//                         kAudioOutputUnitProperty_SetInputCallback,
//                         kAudioUnitScope_Global,
//                         inputElement,
//                         &renderProc,
//                         sizeof(AURenderCallbackStruct));
//    CheckStatus(status, @"setRenderCallback MicroPhone -> callback", YES);
//    
//    
//    AURenderCallbackStruct playProc;
//    playProc.inputProc = playCallback;
//    playProc.inputProcRefCon = (__bridge void*)self;
//    status = AudioUnitSetProperty(_ioUnitInstance1,
//                         kAudioUnitProperty_SetRenderCallback,
//                         kAudioUnitScope_Global,
//                         outputElement,
//                         &playProc,
//                         sizeof(AURenderCallbackStruct));
//    CheckStatus(status, @"setRenderCallback callback -> Speaker", YES);
//}
//
//static OSStatus renderCallback(void *inRefCon,
//                               AudioUnitRenderActionFlags *ioActionFlags,
//                               const AudioTimeStamp *inTimeStamp,
//                               UInt32 inBusNumber,
//                               UInt32 inNumberFrames,
//                               AudioBufferList *ioData) {
//    OSStatus result = noErr;
//    
//    AudioManager *audioManager = (__bridge AudioManager*)inRefCon;
//    
//    AudioBuffer buffer;
//    buffer.mDataByteSize = inNumberFrames * sizeof(Float32); // sample size
//    buffer.mNumberChannels = 1; // one channel
//    buffer.mData = malloc( inNumberFrames * 2 ); // buffer size
//    
//    // we put our buffer into a bufferlist array for rendering
//    AudioBufferList bufferList;
//    bufferList.mNumberBuffers = 1;
//    bufferList.mBuffers[0] = buffer;
//    
//    OSStatus status;
//    status = AudioUnitRender(player.inputUnit,
//                             ioActionFlags,
//                             inTimeStamp,
//                             inBusNumber,
//                             inNumberFrames,
//                             &bufferList);
//
//    
//    
//    
//    return result;
//}
//
//static OSStatus playCallback(void *inRefCon,
//                             AudioUnitRenderActionFlags *ioActionFlags,
//                             const AudioTimeStamp *inTimeStamp,
//                             UInt32 inBusNumber,
//                             UInt32 inNumberFrames,
//                             AudioBufferList *ioData) {
//    return noErr;
//}
//
//
//
//static void CheckStatus(OSStatus status, NSString* message, BOOL fatal) {
//    if (status != noErr) {
//        NSLog(@"status[%d] msg[%@]", status, message);
//        
//        if (fatal) {
//            exit(-1);
//        }
//    }
//}
//
//
//-(void) setAudioSessionConfigWithCategory:(AVAudioSessionCategory)category mode:(AVAudioSessionMode)mode options:(AVAudioSessionCategoryOptions)options error:(NSError**)outError {
//    AVAudioSession* session = [AVAudioSession sharedInstance];
//    
//    AVAudioSessionCategory curCategory = [session category];
//    AVAudioSessionMode curMode = [session mode];
//    AVAudioSessionCategoryOptions curOptions = [session categoryOptions];
//    
//    _prevCategory = curCategory;
//    _prevMode = curMode;
//    _prevOptions = options;
//    
//    if (curCategory != category
//        || curMode != mode
//        || curOptions != options) {
//        [session setCategory:category mode:mode options:options error:outError];
//    }
//}
//
//-(void) configAudioSession {
//    NSError* configError = nil;
//    [self setAudioSessionConfigWithCategory:AVAudioSessionCategoryPlayAndRecord mode:AVAudioSessionModeVideoChat options: (AVAudioSessionCategoryOptionDefaultToSpeaker | AVAudioSessionCategoryOptionAllowBluetooth) error:&configError];
//    NSLog(@"configAudioSession error[%@]", configError);
//    
//    AVAudioSession* session = [AVAudioSession sharedInstance];
//    NSTimeInterval bufferDuration = 0.002;
//    [session setPreferredIOBufferDuration:bufferDuration error:&configError];
//    NSLog(@"setPreferedIOBufferDuration error[%@]", configError);
//    
//    double sampleRate = _sampleRate; //44.1kHz
//    [session setPreferredSampleRate:sampleRate error:&configError];
//    NSLog(@"setPreferredSampleRate error[%@]", configError);
//    
//    [session setActive:YES error:&configError];
//    NSLog(@"setActive error[%@]", configError);
//}
//
//-(void) recoverAudioSessionConfig {
//    NSError* recoverError = nil;
//    [self setAudioSessionConfigWithCategory:_prevCategory mode:_prevMode options:_prevOptions error:&recoverError];
//    NSLog(@"recoverAudioSesionConfig error[%@]", recoverError);
//    
//    [[AVAudioSession sharedInstance] setActive:NO error:&recoverError];
//    NSLog(@"deActive error[%@]", recoverError);
//}
//
//
//
//
//
//
//
//@end
