//
//  LightSettingInfo.h
//  NVSDK
//
//  Created by qin on 2020/7/18.
//  Copyright © 2020 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface LightSettingInfo : NSObject

@property (nonatomic,assign) int total; //已设置的控制命令总数
/**
 默认动作
 0：自动；1：打开，2：关闭
 */
@property (nonatomic,assign) int defaultAction;
/**
 灯光能力
 0：可以长亮；大于0，表示最长亮时长，单位为分钟
 */
@property (nonatomic,assign) int capability;
/**
 命令动作
 0：自动；1：打开，2：关闭
 */
@property (nonatomic,assign) int action;
/**
 命令执行开始时间
 */
@property (nonatomic,assign) int sHour;
@property (nonatomic,assign) int sMinute;
@property (nonatomic,assign) int sSecond;
/**
 命令执行结束时间
 */
@property (nonatomic,assign) int eHour;
@property (nonatomic,assign) int eMinute;
@property (nonatomic,assign) int eSecond;
/**
 警戒灯主开关：0：不支持；1：开启，10：关闭
 */
@property (nonatomic,assign) int mainSwitch;
/**
 移动侦测警戒灯：0：不支持；1：开启，10：关闭
 */
@property (nonatomic,assign) int motionDetectionSwitch;
/**
 人形侦测警戒灯：0：不支持；1：开启，10：关闭
 */
@property (nonatomic,assign) int humanDetectionSwitch;
/**
 指示灯状态-开关：0：不支持；1：开启，10：关闭
 */
@property (nonatomic,assign) int indicatorSwitch;

@end

NS_ASSUME_NONNULL_END
