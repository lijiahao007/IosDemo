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
- (instancetype)initWithStartSecond:(int)startSecnd endSecond:(int)endSecond;
@end

NS_ASSUME_NONNULL_END
