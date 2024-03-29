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

- (instancetype)initWithSampleRate:(int)sampleRate enableRecord:(BOOL)enableRecord enablePlay:(BOOL)enablePlay rate:(float)rate;

- (void)play;
- (void)stop;

- (BOOL)enableRecord;
- (BOOL)enablePlay;

- (BOOL)isRunning;

@end

NS_ASSUME_NONNULL_END
