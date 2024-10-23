//
//  TimeInfo.m
//  MyApplication
//
//  Created by HS on 2024/10/23.
//

#import "TimeRulerInfo.h"

@implementation TimeRulerInfo
- (instancetype)initWithStartSecond:(int)startSecnd endSecond:(int)endSecond {
    self = [super init];
    if (self) {
        _startSecond = startSecnd;
        _endSecond = endSecond;
    }
    return self;
}
@end
