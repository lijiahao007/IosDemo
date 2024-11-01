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

@protocol TimeRulerDelegate <NSObject>

/**
 结束滚动时，停留的秒数
 */
-(void) timeRulerScrollDidEndWithSecond:(CGFloat)currentSeconds;

/**
 滚动时的经过的秒数。
 */
-(void) timeRulerDidScroll:(CGFloat)currentSecond;

@end


NS_ASSUME_NONNULL_BEGIN
@class TimeRulerInfo;
@interface TimeRuler : UIControl
@property(nonatomic, assign) TimeRulerStyle style;
@property (nonatomic, weak) id<TimeRulerDelegate> delegate;

-(void) setSelectedRange:(NSArray<TimeRulerInfo*>*)rangeArray;
- (void)setCurrentTime:(NSInteger)currentTime;
- (BOOL)isEditing;
@end

NS_ASSUME_NONNULL_END
