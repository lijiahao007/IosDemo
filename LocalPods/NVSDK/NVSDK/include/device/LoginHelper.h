//
//  LoginHelper.h
//  iCamSee
//
//  Created by macrovideo on 15/10/14.
//  Copyright © 2015年 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NVDevice.h"
#import "LoginHandle.h"
#import "NVDeviceStatus.h"
#import "SearchDeviceResult.h"
#import "LoginParam.h"
@interface LoginHelper : NSObject

# pragma mark --- new SDK begin ---
+(void)loginDevice:(LoginParam *)loginParam;
+(NVDeviceStatus *)getDeviceStatus:(NVDevice *)device;
+(BOOL)cancel;
+(BOOL)finish;
# pragma mark === new SDK end   ===

#pragma mark ---- old sdk begin
// modify by qiumuze 20170712  局域网登录-fail-->互联网登录
+ (LoginHandle *)getDeviceParam:(NVDevice *)device withConnectType: (int8_t)connectType;
// end modify by qiumuze 20170712

+(LoginHandle *)getDeviceParam:(NVDevice *)device mrserver:(NSString *)strMRServer mrport:(int) nMRPort;

+(NVDeviceStatus *)getDeviceOnlineStat:(NVDevice *)device;

+(BOOL)Cancel;

+ (LoginHandle *)getDeviceParamFromDevice:(NVDevice *)device withConnectType: (int8_t)connectType;
+ (LoginHandle *)getDeviceParamFromMRServer:(NVDevice *)device withConnectType: (int8_t)connectType;
+(BOOL)Finish;

/*
 为了不影响原有的登录逻辑,新增接口:(因为整个逻辑链是在主线程执行的)
 解决oversea AP 局域网登录失败后,仍然到服务器查询,导致快配卡UI问题
 */
//add by weibin 20181108
+ (LoginHandle *)getDeviceParamForOversea:(NVDevice *)device withConnectType: (int8_t)connectType;
//add end by weibin 20181108
#pragma mark ==== old sdk end

+(SearchDeviceResult*)searchDeviceFromServer:(NVDevice *)device;
+(SearchDeviceResult*)searchDeviceFromServer:(NVDevice *)device withStamp:(int)stamp;//add by qin 20210513
+(BOOL)hasFetchedNVDeviceConfigInfo:(NVDevice*)device;//added for test 20190412 by weibin
@end
