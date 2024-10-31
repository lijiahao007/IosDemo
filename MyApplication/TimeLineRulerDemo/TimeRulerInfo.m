//
//  TimeInfo.m
//  MyApplication
//
//  Created by HS on 2024/10/23.
//

#import "TimeRulerInfo.h"

@implementation TimeRulerInfo
- (instancetype)initWithStartSecond:(int)startSecnd endSecond:(int)endSecond color:(UIColor*)color priority:(CGFloat)priority{
    self = [super init];
    if (self) {
        _startSecond = startSecnd;
        _endSecond = endSecond;
        _color = color;
        _priority = priority;
    }
    return self;
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"TimeRulerInfo {s:%d e:%d priority:%f}", _startSecond, _endSecond, _priority];
}
@end
