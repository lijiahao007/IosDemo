//
//  AlarmTimeModel.h
//  datepicker
//
//  Created by 视宏 on 17/2/22.
//  Copyright © 2017年 视宏. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef enum : NSUInteger {
    PowerType_Low, // 低功耗
    PowerType_Medium, // 中功耗
    PowerType_High, // 高功耗
} PowerType;

#define POWER_RED_TEXT_COLOR [UIColor colorWithHexString:@"#FF5F52"]
#define POWER_YELLOW_TEXT_COLOR [UIColor colorWithHexString:@"#FEBF28"]
#define POWER_GREEN_TEXT_COLOR [UIColor colorWithHexString:@"#2AD88A"]



@interface AlarmTimeModel : NSObject
/**
id
 */
@property(nonatomic,assign) int timeID;
/**
 报警时间段
 开始时间 HH:mm:ss
 */
@property(nonatomic,strong) NSDate *beginTime;
/**
 报警时间段
 结束时间 HH:mm:ss
 */
@property(nonatomic,strong) NSDate *endTime;
/**
 是否选择
 */
@property(nonatomic,assign) BOOL isSelect;
/**
报警类型(新平台)
 */
@property(nonatomic,assign) int mode;

/**
 计算时间间隔
 return 秒
 */
-(NSInteger) calDuration;
@end
