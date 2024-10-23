//
//  TimeRulerLayer.h
//  MyApplication
//
//  Created by HS on 2024/10/23.
//

#import <QuartzCore/QuartzCore.h>
NS_ASSUME_NONNULL_BEGIN
@class TimeRulerInfo;
@interface TimeRulerLayer : CALayer
@property (nonatomic, strong) NSArray<TimeRulerInfo*>* selectedRange;
@property (nonatomic, class, readonly) CGFloat sideOffset;
@property (nonatomic, class, readonly) CGFloat rulerMaxWidth;
@end

NS_ASSUME_NONNULL_END
