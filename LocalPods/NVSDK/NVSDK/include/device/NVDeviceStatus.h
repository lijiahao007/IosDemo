//
//  NVDeviceStatus.h
//  NVSDK
//
//  Created by caffe on 2019/2/20.
//  certified by caffe on 20190322
//  Copyright © 2019 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NVDeviceStatus : NSObject
@property (assign) int nResult;
@property (assign) int nOnlineStatus;
@property (assign) int nAlarmStatus;
@property(nonatomic,assign) int deviceSoftwareUpdateStatus;//设备升级状态 0 未知 1 不升级 2需要提示升级
@end

NS_ASSUME_NONNULL_END
