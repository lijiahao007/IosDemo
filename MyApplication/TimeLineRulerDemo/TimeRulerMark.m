//
//  TimeRulerMask.m
//  MyApplication
//
//  Created by HS on 2024/10/23.
//

#import "TimeRulerMark.h"

@implementation TimeRulerMark
- (instancetype)init
{
    self = [super init];
    if (self) {
        _color = [[UIColor alloc]initWithWhite:0.78 alpha:1.0];
        _font = [UIFont systemFontOfSize:9.0];
        _textColor = [[UIColor alloc]initWithWhite:0.43 alpha:1.0];
    }
    return self;
}
@end
