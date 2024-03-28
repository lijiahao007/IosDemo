//
//  AudioViewController.m
//  MyApplication
//
//  Created by package on 2024/3/28.
//

#import "AudioViewController.h"
#import "AudioOutput.h"
#import <AVFoundation/AVFoundation.h>
#import "PermissionManager.h"

@interface AudioViewController () <AudioOutputDelegate>
@property (nonatomic, strong) AudioOutput* audioOutput;
@end

@implementation AudioViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    NSError* setCategoryError = nil;
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord mode:AVAudioSessionModeVideoChat options:AVAudioSessionCategoryOptionDefaultToSpeaker error:&setCategoryError];
    NSLog(@"AudioSession startTalk setCategory AVAudioSessionCategoryPlayAndRecord AVAudioSessionCategoryPlayAndRecord AVAudioSessionCategoryOptionDefaultToSpeaker error[%@]", setCategoryError);
    [[AVAudioSession sharedInstance] setActive:YES error:&setCategoryError];
    NSLog(@"AudioSession startTalk setActive error[%@]", setCategoryError);
    
    float bufferDuration = 0.064;
    [self SetAudioSessionWithTime:bufferDuration];


}

- (IBAction)startPlay:(id)sender {
    
    X_WeakSelf
    [PermissionManager checkRecordPermission:^(BOOL isPermission) {
        X_StrongSelf
        if (!isPermission) {
            return;
        }
        if (strongSelf.audioOutput == nil) {
            strongSelf.audioOutput = [[AudioOutput alloc]init];
            strongSelf.audioOutput.delegate = strongSelf;
        }
        
        [strongSelf.audioOutput play];
    }];
  
}

- (IBAction)stopPlay:(id)sender {
    if (_audioOutput) {
        [_audioOutput stop];
    }
}


- (void)getRecordData:(nullable SInt8 *)buffer byteSize:(int)byteSize { 
    NSLog(@"getRecordData byteSize:%d", byteSize);
}

- (void)requestAudioFrame:(nonnull SInt16 *)buffer numFrames:(int)numFrames { 
    NSLog(@"requestAudioFrame numFrames:%d", numFrames);
    memset(buffer, 0, sizeof(SInt16) * numFrames);
}


-(void)SetAudioSessionWithTime:(NSTimeInterval)second{
    AVAudioSession* session = [AVAudioSession sharedInstance];
    [session setPreferredSampleRate:16000 error:nil];
    [session setPreferredIOBufferDuration:second error:nil];
    [session setActive:YES error:nil];
    
}


@end
