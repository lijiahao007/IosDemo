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
@property (nonatomic, assign) float rate;
@property (weak, nonatomic) IBOutlet UILabel *gainNumLabel;

@property (nonatomic, strong) NSData* pcmRawData;
@property (nonatomic, assign) NSUInteger offset;

@end

@implementation AudioViewController

- (instancetype)init
{
    self = [super init];
    if (self) {
        _rate = 1.0f;
    }
    return self;
}

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

    _playSwitch.on = YES;
    _recordSwitch.on = YES;
    [_playSwitch addTarget:self action:@selector(switchStateChange:) forControlEvents:UIControlEventValueChanged];
    [_recordSwitch addTarget:self action:@selector(switchStateChange:) forControlEvents:UIControlEventValueChanged];
    
    if (_audioOutput == nil) {
        _audioOutput = [[AudioOutput alloc]initWithSampleRate:16000 enableRecord:NO enablePlay:NO rate:_rate];
        _audioOutput.delegate = self;
    }
    self.rateLabel.text = [NSString stringWithFormat:@"%.2f", self.audioOutput.rate];
    self.playSwitch.on = self.audioOutput.enablePlay;
    self.recordSwitch.on = self.audioOutput.enableRecord;
    self.gainNumLabel.text = [NSString stringWithFormat:@"%.2f", self.audioOutput.overallGain];
    
    [self loadPcmData];
}

-(void) loadPcmData {
    NSURL* url = [[NSBundle mainBundle]URLForResource:@"pcm_raw_data" withExtension:@"raw"];
    _pcmRawData = [NSData dataWithContentsOfURL:url];
    NSLog(@"loadPcmData:%lu", _pcmRawData.length);
}

- (IBAction)startPlay:(id)sender {
    
    X_WeakSelf
    [PermissionManager checkRecordPermission:^(BOOL isPermission) {
        X_StrongSelf
        if (!isPermission) {
            return;
        }
        
        strongSelf.audioOutput.rate = strongSelf.rate;
        [strongSelf.audioOutput play];
    }];
  
}

- (IBAction)plusGain:(id)sender {
    if (self.audioOutput) {
        self.audioOutput.overallGain++;
        self.gainNumLabel.text = [NSString stringWithFormat:@"%.2f", self.audioOutput.overallGain];
    }
}

- (IBAction)minusGain:(id)sender {
    if (self.audioOutput) {
        self.audioOutput.overallGain--;
        self.gainNumLabel.text = [NSString stringWithFormat:@"%.2f", self.audioOutput.overallGain];
    }
}

- (IBAction)stopPlay:(id)sender {
    if (_audioOutput) {
        [_audioOutput stop];
    }
}
- (IBAction)clickPlus:(id)sender {
    float rate = _rate + 0.1;
    rate = MIN(32.0, rate);
    _rate = rate;
    
    if (_audioOutput) {
        _audioOutput.rate = _rate;
    }
    
    _rateLabel.text = [NSString stringWithFormat:@"%.2f", _rate];

}

- (IBAction)clickMinus:(id)sender {
    float rate = _rate - 0.1;
    rate = MAX(1/32.0, rate);
    _rate = rate;
    
    if (_audioOutput) {
        _audioOutput.rate = _rate;
    }
    
    _rateLabel.text = [NSString stringWithFormat:@"%.2f", _rate];
}

- (void)getRecordData:(nullable SInt8 *)buffer byteSize:(int)byteSize { 
    
    NSMutableString* str = [NSMutableString new];
    for (int i = 0; i < byteSize && i < 10; i++) {
        [str appendFormat:@"%d ", buffer[i]];
    }
    
    NSLog(@"getRecordData byteSize:%d  %@  %@", byteSize, str, [NSThread currentThread]);
    
}

- (void)requestAudioFrame:(nonnull SInt16 *)buffer numFrames:(int)numFrames {
    long now = [self getNowMillis];
    long distance = now - self.prevTime;
    self.prevTime = now;
    NSLog(@"requestAudioFrame numFrames:%d dis:[%ld]  %@", numFrames, distance, [NSThread currentThread]);
    
    int needBytes = sizeof(SInt16) * numFrames;
    NSUInteger rawDataLength = _pcmRawData.length;
    if (needBytes + _offset < rawDataLength) {
        [_pcmRawData getBytes:buffer range:NSMakeRange(_offset, needBytes)];
        _offset += needBytes;
    } else {
        NSUInteger firstPartLength = rawDataLength - _offset;
        [_pcmRawData getBytes:buffer range:NSMakeRange(_offset, firstPartLength)];
        NSUInteger secondPartLength = needBytes - firstPartLength;
        [_pcmRawData getBytes:buffer + firstPartLength range:NSMakeRange(0, secondPartLength)];
        _offset = secondPartLength;
    }
    
    X_WeakSelf
    dispatch_async(dispatch_get_main_queue(), ^{
        X_StrongSelf
        strongSelf.rateLabel.text = [NSString stringWithFormat:@"%.2f", strongSelf.audioOutput.rate];
    });
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
    
    if (sender == self.playSwitch) {
        self.audioOutput.enablePlay = sw.on;
    } else if (sender == self.recordSwitch) {
        self.audioOutput.enableRecord = sw.on;
    }
    
}


@end
