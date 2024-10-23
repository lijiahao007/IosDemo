//
//  TimeRulerMask.h
//  MyApplication
//
//  Created by HS on 2024/10/23.
//

#import <Foundation/Foundation.h>

typedef enum : int {
    RulerMarkFrequency_Hour = 3600, //小时标记频率3600秒
    RulerMarkFrequency_Minute_10 = 600, //10分钟标记频率
    RulerMarkFrequency_Minute_2 = 120, //2分钟标记频率
    // 如需要更小时间在此添加枚举值
} RulerMarkFrequency;

NS_ASSUME_NONNULL_BEGIN

/**
 时间刻度
 */
@interface TimeRulerMark : NSObject

@property (nonatomic, assign) RulerMarkFrequency frequency;
@property (nonatomic, assign) CGSize size;
@property (nonatomic, copy) UIColor* color;
@property (nonatomic, copy) UIFont* font;
@property (nonatomic, copy) UIColor* textColor;

@end

NS_ASSUME_NONNULL_END
