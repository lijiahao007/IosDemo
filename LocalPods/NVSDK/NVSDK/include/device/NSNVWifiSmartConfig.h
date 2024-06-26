//
//  NSNVWifiSmartConfig.h
//  iCamSee
//
//  Created by macrovideo on 15/7/25.
//  Copyright (c) 2015年 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

#define SEND_RESULT_READY               0x0   //发送就绪
#define SEND_RESULT_FINISH              0x10  //发送完成
#define SEND_RESULT_FAIL                -0x11 //发送失败
#define SEND_RESULT_CONFIG_ID_FMT_ERR   -0x12 //配置id格式不对（要求1-9）
#define SEND_RESULT_SSID_ERR            -0x13 //ssid为空不对
#define SEND_RESULT_PWD_FMT_ERR         -0x14 //密码格式不对（要求为空或8个以上字符）

@interface NSNVWifiSmartConfig : NSObject 

#pragma mark -- new SDK begin ---
+(int)startSmartConnection:(NSString *)strSSID PWD:(NSString *)strPassword configID:(int)nConfigID;
+(int)stopSmartConnection;
#pragma mark == new SDK end   ===

#pragma mark --- old sdk begin
+(int)StartSmartConnectionSSID:(NSString *)strSSID PWD:(NSString *)strPassword configID:(int)nConfigID;
+(int)StopSmartConnection;
#pragma mark === old sdk end

@end
