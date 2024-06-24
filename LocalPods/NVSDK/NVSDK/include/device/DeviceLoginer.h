//
//  DeviceLoginer.h
//  NVSDK
//
//  Created by VINSON on 2019/7/16.
//  Copyright © 2019 macrovideo. All rights reserved.
//

/**
 FIXME: 优化
 对于这个Loginer，还是设计不太好，现在内部实现有点混乱，尤其在添加Multi重新登录的逻辑之后尤其明显；
 故提出以下优化点：
 1. 对外接口只保留multiLoginByLanIP；
 2. 内部DeviceLoginProcessMaster和DeviceLoginProcess这两个需要分离，设计初期是不考虑MultiLogin这个逻辑包含其中才有这个继承，
    需要外部多次调用loginByLanIP: NetIPArray: ，从而产生不同的process；
 */

#import <Foundation/Foundation.h>
#import "LoginHandle.h"
#import "NVDeviceAbility.h"
#import "LanpassResult.h"
typedef enum : NSUInteger {
    DeviceLoginResultSucceed,
    DeviceLoginResultEmptyPassword,
    DeviceLoginResultMistakeUserNameOrPassword,
    DeviceLoginResultConnectFailure,
    DeviceLoginResultWeakPassword,
} DeviceLoginResult;

@class DeviceLoginProcess;
@interface DeviceLoginProcess : NSObject
@property (nonatomic,copy,nullable) __attribute__((deprecated("此回调即将私有，请使用onMultiFinished"))) void(^onFinished)(LoginHandle * _Nullable handle);
@property (nonatomic,copy,nullable) void(^onMultiFinished)(LoginHandle * _Nullable handle, DeviceLoginResult resule);
@property (nonatomic,copy,nullable) void(^onMultiAndAbilityFinished)(LoginHandle * _Nullable handle,NVDeviceAbility * _Nullable deviceAbility, DeviceLoginResult resule);
@property (nonatomic,copy,nullable) void(^onLanPassFinished)(LanpassResult * _Nullable result);

-(BOOL)cancel;
@end

NS_ASSUME_NONNULL_BEGIN
@interface DeviceLoginer : NSObject
+(void)cancel;
//局域网登录: 新协议
+ (DeviceLoginProcess*) loginByLanIP:(NSString*)ip
                                Port:(int)port
                            DeviceID:(int)deviceID
                            UserName:(NSString*)userName
                            Password:(NSString*)password __attribute__((deprecated("此函数即将私有，请使用multiLoginByLanIP，包含了一些空密码、弱密码等多次登录")));
//双线程登录
+ (DeviceLoginProcess*) multiLoginByLanIP:(NSString *)ip
                               NetIPArray:(NSArray<NSString *> *)netIPArray
                                     Port:(int)port
                                 DeviceID:(int)deviceID
                                 UserName:(NSString *)userName
                                 Password:(NSString *)password
                              ConnectType:(int)connectType
                                subServer:(NSString *)subServer
                                AccountID:(int)account
                                method:(NSString*)method;

/**新平台（无需登录）：获取设备能力及属性（预览相关）
 flag:预览YES，进入远程配置NO
 **/
+ (DeviceLoginProcess*) getAbilityAndConfigInfoForPreviewFromDevice:(NVDevice*)device flag:(BOOL)flag;
/**
 新平台局域网鉴权及修改密码
 @params action
 0=无效
 1=校验/鉴权
 2=密码更改
 3=密码重置动态凭证RDH生成
 4=密码重置
 
 @return 详见ResultCodeV30.h
 */
+(DeviceLoginProcess*)landPassVerify:(NVDevice *)device action:(int)action;
@end

NS_ASSUME_NONNULL_END
