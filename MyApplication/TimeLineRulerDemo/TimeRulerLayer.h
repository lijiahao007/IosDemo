//
//  TimeRulerLayer.h
//  MyApplication
//
//  Created by HS on 2024/10/23.
//

#import <QuartzCore/QuartzCore.h>
#define kScaleDefaultFontSize       9.0  //刻度字体
#define kScaleDefaultColor          ([UIColor lightGrayColor])  //刻度颜色、文字颜色

typedef enum : NSUInteger {
    TimeRulerLayer_TextCenter,
    TimeRulerLayer_TextTop,
} TimeRulerLayerTextPosition;


NS_ASSUME_NONNULL_BEGIN
@class TimeRulerInfo;
@interface TimeRulerLayer : CALayer
@property (nonatomic, assign) TimeRulerLayerTextPosition textPosition;
@property (nonatomic, copy) NSArray<TimeRulerInfo*>* selectedRange;
@property (nonatomic, class, readonly) CGFloat sideOffset;
@property (nonatomic, class, readonly) CGFloat rulerMaxWidth;
@property (nonatomic, assign) BOOL showTopMark;
@property (nonatomic, assign) BOOL showBottomMark;
@property (nonatomic, strong) UIColor* timeTextColor;
@end

NS_ASSUME_NONNULL_END
