//
//  DebugView.h
//  test
//
//  Created by master on 2024/3/8.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface DebugView : UIView
+ (DebugView*)sharedInstance;
-(void)addLogText:(NSString *)text;
-(void)closeView;
@end

NS_ASSUME_NONNULL_END
