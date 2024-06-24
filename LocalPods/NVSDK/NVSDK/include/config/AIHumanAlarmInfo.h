//
//  AIHumanAlarmInfo.h
//  NVSDK
//
//  Created by master on 2022/10/11.
//  Copyright © 2022 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AIHumanAlarmInfo : NSObject

/**
 AI人形检测开关，01：开 10：关 （0：无效/不支持）
 */
@property (nonatomic ,assign) int AIHumanDetectEnable;
/**
 AI人形识别框开关，01：开 10：关
 */
@property (nonatomic ,assign) int AIHumanFrameEnable;
/**
 AI人形侦测灵敏度，0：无效/不支持 01：低，02：中， 03： 高，10：关闭
 */
@property (nonatomic ,assign) int AIHumanSensitivity;
/**
 AI报警语音提示开关，01：开 10：关 （0：无效/不支持）
 */
@property (nonatomic ,assign) int AIAlarmNoticeEnable;
/**
 AI时间区域使能 01：有 10：无
 */
@property (nonatomic ,assign) int AITimeCtrlEnable;
/**
 AI时间段
 */
@property (nonatomic ,strong) NSMutableArray *AITimeSettings;
/**
 AI报警区行数
 */
@property (nonatomic ,assign) int AIRow;
/**
 AI报警区列数
 */
@property (nonatomic ,assign) int AIColumn;
/**
 AI报警区域 row * column
 */
@property (nonatomic ,strong) NSMutableArray *AIAlarmArea;
/**
 AI报警提示音类型，0：不支持切换，1：默认类型，2：自定义类型
 */
@property (nonatomic ,assign) int AIVoiceType;
/**
 AI报警警戒灯开关　00: 不支持　01:开　10:关
 */
@property (nonatomic ,assign) int AIDetectAlert_light_switch;

@end

NS_ASSUME_NONNULL_END
