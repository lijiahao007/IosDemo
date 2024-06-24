//
//  TimeAlbumInfo.h
//  NVSDK
//
//  Created by master on 2022/9/26.
//  Copyright © 2022 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ScenesItem : NSObject<NSCopying>
/**
 数据类型，1=图片，2=视频
 */
@property (nonatomic ,assign) int type;
/**
 场景名称，最大32个字符
 */
@property (nonatomic ,copy) NSString *name;
/**
 场景开始时间
 */
@property (nonatomic ,assign) long startTime;
/**
 首次触发实际时间
 */
@property (nonatomic ,assign) long realTime;
/**
 场景结束时间，相对开始时间的偏移时间（秒）
 */
@property (nonatomic ,assign) int endOffSet;
/**
 触发场景持续时间（秒）
 */
@property (nonatomic ,assign) long taskDuration;
/**
 触发上传间隔（秒）
 */
@property (nonatomic ,assign) long taskShotInterval;
/**
 到下一个触发场景开始的时间间隔（秒）
 */
@property (nonatomic ,assign) long nextTaskInterval;

@end

@interface TimeAlbumInfo : NSObject
/**
 配置唯一标识（随机）
 */
@property (nonatomic ,assign) int flag;
/**
 时光场景数（最大为2个）
 */
@property (nonatomic ,assign) int count;
/**
 时光场景数数组
 */
@property (nonatomic ,strong) NSMutableArray *scenes;;
/**
uid
 */
@property (nonatomic ,assign) int uid;

@end

NS_ASSUME_NONNULL_END
