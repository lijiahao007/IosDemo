//
//  RecordVideoHelper.h
//  NVSDK
//
//  Created by caffe on 2019/2/23.
//  certified by caffe 20190325
//  Copyright © 2019 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LoginHandle.h"
#import "NVDevice.h"
#import "RecFileSearchDelegate.h"
#import "RecordFileParam.h"
NS_ASSUME_NONNULL_BEGIN

@interface RecordVideoHelper : NSObject
+(int)getRecordVideoInTFCard:(LoginHandle *)loginHandle receiver:(id<RecFileSearchDelegate>)delegate fileParam:(RecordFileParam *)param;

//iot
+(int)getRecordVideoFromDevice:(NVDevice *)device receiver:(id<RecFileSearchDelegate>)delegate fileParam:(RecordFileParam *)param;

+(BOOL)cancelOperation;//取消操作

#pragma mark ---- 这个函数后续需要删除 caffedelete
//+(LoginHandle *)getRecordOPHandle:(NVDevice *)device withConnectType:(UInt8)connectType;//获取操作句柄 // modify by qiumuze 20170726
@end

NS_ASSUME_NONNULL_END
