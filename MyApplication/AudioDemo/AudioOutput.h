//
//  AudioPlayer.h
//  NVSDK
//
//  Created by package on 2024/3/27.
//  Copyright © 2024 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol AudioOutputDelegate <NSObject>

// 申请需要渲染的数据 （不要阻塞）
-(void) requestAudioFrame:(SInt16*)buffer numFrames:(int)numFrames;

// 给外层抛出录音数据 (不要阻塞)
-(void) getRecordData:(nullable SInt8*)buffer byteSize:(int)byteSize;
@end

@interface AudioOutput : NSObject

@property (nonatomic, weak) id<AudioOutputDelegate> delegate;
@property (nonatomic, assign) float rate; // 播放速率 [1/32,32.0]
@property (nonatomic, assign) BOOL enableRecord; // 是否启动录音
@property (nonatomic, assign) BOOL enablePlay; // 是否启动播放
@property (nonatomic, assign) float overallGain; // 增益 [-40db, 40db]

- (instancetype)initWithSampleRate:(int)sampleRate enableRecord:(BOOL)enableRecord enablePlay:(BOOL)enablePlay rate:(float)rate;

- (void)play;
- (void)stop;

- (BOOL)isRunning;

@end

NS_ASSUME_NONNULL_END
