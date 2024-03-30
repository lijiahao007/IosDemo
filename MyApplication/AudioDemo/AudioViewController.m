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
@property (weak, nonatomic) IBOutlet UILabel *rateLabel;
@property (nonatomic, strong) AudioOutput* audioOutput;
@property (weak, nonatomic) IBOutlet UISwitch *playSwitch;
@property (weak, nonatomic) IBOutlet UISwitch *recordSwitch;
@property (nonatomic, assign) long prevTime;
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

    _rateLabel.text = [NSString stringWithFormat:@"%.2f", 1.0];
    _playSwitch.on = YES;
    _recordSwitch.on = YES;
    [_playSwitch addTarget:self action:@selector(switchStateChange:) forControlEvents:UIControlEventValueChanged];
    [_recordSwitch addTarget:self action:@selector(switchStateChange:) forControlEvents:UIControlEventValueChanged];
    

    self.rateLabel.text = [NSString stringWithFormat:@"%.2f", self.audioOutput.rate];
    self.playSwitch.on = self.audioOutput.enablePlay;
    self.recordSwitch.on = self.audioOutput.enableRecord;
}

- (IBAction)startPlay:(id)sender {
    
    X_WeakSelf
    [PermissionManager checkRecordPermission:^(BOOL isPermission) {
        X_StrongSelf
        if (!isPermission) {
            return;
        }
        
        if (strongSelf.audioOutput == nil) {
            BOOL enableRecord = strongSelf.recordSwitch.on;
            BOOL enablePlay = strongSelf.playSwitch.on;
            strongSelf.audioOutput = [[AudioOutput alloc]initWithSampleRate:16000 enableRecord:enableRecord enablePlay:enablePlay rate:1.0];
            strongSelf.audioOutput.delegate = self;
        }

        strongSelf.rateLabel.text = [NSString stringWithFormat:@"%f", strongSelf.audioOutput.rate];
        [strongSelf.audioOutput play];
    }];
  
}

- (IBAction)stopPlay:(id)sender {
    if (_audioOutput) {
        [_audioOutput stop];
    }
}
- (IBAction)clickPlus:(id)sender {
    if (_audioOutput) {
        float rate = _audioOutput.rate + 0.1;
        rate = MIN(32.0, rate);
        _audioOutput.rate = rate;
        _rateLabel.text = [NSString stringWithFormat:@"%.2f", _audioOutput.rate];
    }
}

- (IBAction)clickMinus:(id)sender {
    if (_audioOutput) {
        float rate = _audioOutput.rate - 0.1;
        rate = MAX(1.0/32, rate);
        _audioOutput.rate = rate;
        _rateLabel.text = [NSString stringWithFormat:@"%.2f", _audioOutput.rate];
    }
}

- (void)getRecordData:(nullable SInt8 *)buffer byteSize:(int)byteSize { 
    NSLog(@"getRecordData byteSize:%d", byteSize);
}

- (void)requestAudioFrame:(nonnull SInt16 *)buffer numFrames:(int)numFrames {
    long now = [self getNowMillis];
    long distance = now - self.prevTime;
    self.prevTime = now;
    NSLog(@"requestAudioFrame numFrames:%d dis:[%ld]", numFrames, distance);
    memset(buffer, 100, sizeof(SInt16) * numFrames);
}

-(long) getNowMillis {
    return [[NSDate date] timeIntervalSince1970] * 1000;
}


-(void)SetAudioSessionWithTime:(NSTimeInterval)second{
    AVAudioSession* session = [AVAudioSession sharedInstance];
    [session setPreferredSampleRate:16000 error:nil];
    [session setPreferredIOBufferDuration:second error:nil];
    [session setActive:YES error:nil];
    
}

- (void)switchStateChange:(id)sender {
    UISwitch* sw = (UISwitch*) sender;
    if (_audioOutput == nil) return;
    BOOL isRunning = _audioOutput.isRunning;
    BOOL enableRecord = _audioOutput.enableRecord;
    BOOL enablePlay = _audioOutput.enablePlay;
    float rate = _audioOutput.rate;
    
    [_audioOutput stop];
    _audioOutput = nil;
    
    if (sender == self.playSwitch) {
        self.audioOutput = [[AudioOutput alloc]initWithSampleRate:16000 enableRecord:enableRecord enablePlay:sw.on rate:rate];
    } else if (sender == self.recordSwitch) {
        self.audioOutput = [[AudioOutput alloc]initWithSampleRate:16000 enableRecord:sw.on enablePlay:enablePlay rate:rate];
    }
    self.audioOutput.delegate = self;

    self.rateLabel.text = [NSString stringWithFormat:@"%f", self.audioOutput.rate];
    [self.audioOutput play];

}


@end
