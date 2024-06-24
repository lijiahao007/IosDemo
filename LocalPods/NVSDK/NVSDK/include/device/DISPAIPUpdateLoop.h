#import <Foundation/Foundation.h>

//#define CAFFE_DEBUG_DISPATCH                  //指定服务器Debug
NS_ASSUME_NONNULL_BEGIN

@interface DISPAIPUpdateLoop : NSObject
+ (void)start;
+ (void)stop;
+ (nullable NSArray<NSString*>*)getIPArray;
+ (NSDate*) lastUpdateTime;
@end

NS_ASSUME_NONNULL_END
