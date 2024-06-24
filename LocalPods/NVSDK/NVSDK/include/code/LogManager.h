//
//  LogManager.h
//  test
//
//  Created by Yang on 2021/2/4.
//  Copyright © 2021 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

#define AppLogWriteFmt(type,debug,...) [[LogManager sharedInstance] writeAppLogWithType:type showDebug:debug format:[NSString stringWithFormat:__VA_ARGS__]]


NS_ASSUME_NONNULL_BEGIN

// App端行为日志类型
typedef NS_ENUM(NSUInteger, LogType){
    LogTypeAppStartup,        //App启动
    LogTypeLoginLan,             //局域网登录
    LogTypeLoginWan,             //互联网登录
    LogTypeCameraImage,       //请求预览
    LogTypeCameraImageLan,       //局域网请求预览
    LogTypeCameraImageWan,       //互联网请求预览
    LogTypeCameraLoadFilesLan,   //局域网录像搜索
    LogTypeCameraLoadFilesWan,   //互联网录像搜索
    LogTypeCameraReplayImageLan, //局域网请求回放
    LogTypeCameraReplayImageWan, //互联网请求回放
    
    LogTypeGetDispatch,     //新平台获取调度
    LogTypeSecretKey,     //新平台秘钥交换
    LogTypeGetPublickey,     //新平台get Publickey
    LogTypeGetDeviceConfig, //新平台获取设备属性
    LogTypeGetDeviceAbility, //新平台获取设备能力
    LogTypeSetDeviceConfig, //新平台设置设备属性
    LogTypeSetDeviceAction, //新平台设置设备动作
    LogTypeDevicePinCode, //新平台pincode
    LogTypeDeviceQRCode, //新平台二维码
    LogTypeDeviceIPCState, //新平台查询设备状态
    LogTypeDeviceVideoCall, // 带屏设备
    LogTypeMQTT, // MQTT
    LogTypeAudioFrame, // 音频帧率
    LogTypeOther,           //其它
};

@interface LogManager : NSObject
/**
 * 获取单例实例
 *
 * @return 单例实例
 */
+ (instancetype) sharedInstance;
 
#pragma mark - Method
 
/**
 * 写入日志
 *
 * @param type 模块名称
 * @param format 日志信息,动态参数
 */
- (void)writeAppLogWithType:(LogType)type showDebug:(BOOL)debug format:(NSString *)format;

/**
 * 清空过期的日志
 */
- (void)clearExpiredLog;


@end

NS_ASSUME_NONNULL_END
