//
//  TimeConfigInfo.h
//  NVSDK
//
//  Created by caffe on 2019/2/22.
//  cetified by caffe on 20190322
//  Copyright © 2019 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface TimeConfigInfo : NSObject
@property (nonatomic,assign) int nResult;
/**
 时间格式：0和1表示第一版协议，2：已经支持半时区 3：已经支持时间格式设置
 */
@property (nonatomic,assign) int nDateType;
/**
 时区开关
 */
@property (nonatomic,assign) BOOL bTimeZoneEnable;
/**
 时区
 */
@property (nonatomic,assign) int nTimeZone;
/**
 当前时间
 */
@property (nonatomic,copy) NSString *strDateTime;
/**
 半时区偏移
 */
@property (nonatomic,assign) int overTime;
/**
 OSD用时间格式:12=12小时制,24=24小时制度
 */
@property (assign) int timeFormat;
/**
 夏令时:0=disable,+N=N hours
 */
@property (nonatomic,assign) int dst;
@end

NS_ASSUME_NONNULL_END
