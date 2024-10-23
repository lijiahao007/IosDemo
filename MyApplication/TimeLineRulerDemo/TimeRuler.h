//
//  TimeRuler.h
//  MyApplication
//
//  Created by HS on 2024/10/23.
//

#import <UIKit/UIKit.h>


NS_ASSUME_NONNULL_BEGIN
@class TimeRulerInfo;
@interface TimeRuler : UIControl
-(void) setSelectedRange:(NSArray<TimeRulerInfo*>*)rangeArray;
@end

NS_ASSUME_NONNULL_END
