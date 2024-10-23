//
//  TimelineView.h
//  MyApplication
//
//  Created by HS on 2024/10/23.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface TimelineView : UIView
// 公开属性，允许外部配置
@property (nonatomic, assign) CGFloat timelineHeight;
@property (nonatomic, assign) CGFloat majorTickHeight;
@property (nonatomic, assign) CGFloat minorTickHeight;
@property (nonatomic, strong) UIColor *indicatorColor;
@property (nonatomic, strong) NSDateFormatter *timeFormatter;

@end

NS_ASSUME_NONNULL_END
