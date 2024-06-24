//
//  CPEConfigInfo.h
//  NVSDK
//
//  Created by HS on 2023/7/20.
//  Copyright © 2023 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface CPEConfigInfo : NSObject

/**
 开关　00: 不支持　01:开　10:关
 */
@property(nonatomic, assign)int enabled;

@end

NS_ASSUME_NONNULL_END
