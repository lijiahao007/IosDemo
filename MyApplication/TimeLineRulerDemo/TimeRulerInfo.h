//
//  TimeInfo.h
//  MyApplication
//
//  Created by HS on 2024/10/23.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface TimeRulerInfo : NSObject
@property (nonatomic, assign) int startSecond;
@property (nonatomic, assign) int endSecond;
@property (nonatomic, strong) UIColor* color;
@property (nonatomic, assign) CGFloat priority; //优先级越高，越不会被覆盖。

- (instancetype)initWithStartSecond:(int)startSecnd endSecond:(int)endSecond color:(UIColor*)color priority:(CGFloat)priority;
@end

NS_ASSUME_NONNULL_END
