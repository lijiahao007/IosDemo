//
//  PrivacyModeInfo.h
//  NVSDK
//
//  Created by qin on 2021/9/24.
//  Copyright © 2021 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface PrivacyModeInfo : NSObject

@property (assign) int status;
@property (assign) int timerEnable;
@property (assign) int timerCount;
@property (nonatomic, strong) NSMutableArray *timerArray;

@end

NS_ASSUME_NONNULL_END
