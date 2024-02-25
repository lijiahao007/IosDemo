//
//  AudioChatViewController.m
//  MyApplication
//
//  Created by 李嘉浩 on 2023/12/25.
//

#import "AudioChatViewController.h"

/**
 TODO: 1. 先用AudioUnit、AudioGraph完成录音功能
 TODO: 2. 将录音出来的PCM文件保存到本地。
 TODO: 3. 使用AudioUnit播放对应的录音文件。
 TODO: 4. 使用各种AudioUnit配置来进行测试
 */

@interface AudioChatViewController ()
@property (weak, nonatomic) IBOutlet UIButton *recordBtn;
@property (weak, nonatomic) IBOutlet UIButton *stopRecordBtn;
@property (weak, nonatomic) IBOutlet UIButton *playbackBtn;
@property (weak, nonatomic) IBOutlet UIButton *stopPlaybackBtn;
@end

@implementation AudioChatViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
}


- (IBAction)recordAction:(id)sender {
    
}

- (IBAction)stopRecordAction:(id)sender {
    
}


- (IBAction)playbackAction:(id)sender {
    
}

- (IBAction)stopPlaybackAction:(id)sender {
    
}


@end
