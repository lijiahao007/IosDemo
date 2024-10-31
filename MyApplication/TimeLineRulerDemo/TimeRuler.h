//
//  TimeRuler.h
//  MyApplication
//
//  Created by HS on 2024/10/23.
//  作用：

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSInteger, TimeRulerStyle) {
    TimeRulerStyleDefault = 0,    // 默认（竖屏）
    TimeRulerStyleLandscape        // 横屏模式
};


NS_ASSUME_NONNULL_BEGIN
@class TimeRulerInfo;
@interface TimeRuler : UIControl
@property(nonatomic, assign) TimeRulerStyle style;
-(void) setSelectedRange:(NSArray<TimeRulerInfo*>*)rangeArray;
@end

NS_ASSUME_NONNULL_END
