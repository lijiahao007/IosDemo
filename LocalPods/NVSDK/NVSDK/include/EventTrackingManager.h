//
//  PreviewEventTrackingManager.h
//  NVSDK
//
//  Created by HS on 2023/9/13.
//  Copyright © 2023 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - 监听消息key
#define koType      @"type"     //事件类型
#define koResult    @"result"   //事件结果
#define koMessage   @"message"  //附加信息
#define koDeviceID  @"deviceID" //事件触发设备ID
#define koServer    @"server"   //连接的服务器ip/域名

typedef NS_ENUM(NSUInteger, EventTrackingType) {
    //预览连接埋点
    EventTrackingTypePreviewLogin                = 10000, //点击登录
    EventTrackingTypePreviewLoginConnectRequest  = 10001, //登录连接请求
    EventTrackingTypePreviewLoginResult          = 10002, //登录结果
    EventTrackingTypePreviewPlay                 = 10003, //预览
    EventTrackingTypePreviewPlayConnectRequest   = 10004, //预览连接请求
    EventTrackingTypePreviewPlayConnectResult    = 10005, //预览连接响应
    EventTrackingTypePreviewPlayResult           = 10006, //出图
};

/*
 部分埋点事件发生在sdk中，这时候需要sdk外部设置监听，由sdk内部代码发送消息通知外部调用埋点上传函数，记得取消监听
 */
@interface EventTrackingManager : NSObject

@property(nonatomic,strong)NSString *appVersion;
@property(nonatomic,assign)int64_t eventNO;
@property(nonatomic,assign)int64_t eventContext;

/// 单例
+(EventTrackingManager*) sharedInstance;

/// 设置监听事件
/// - Parameters:
///   - observer: 要监听事件的对象
///   - selector: 监听到事件后调用的函数
///   - event: 事件类型
-(void)addObserver:(id)observer selector:(SEL)selector event:(EventTrackingType)type;

/// 取消监听事件
/// - Parameters:
///   - observer: 要取消监听事件的对象
///   - event: 事件类型
-(void)removeObserver:(id)observer event:(EventTrackingType)type;

/// 发送事件通知
/// - Parameters:
///   - type: 事件类型
///   - result: 事件结果
///   - message: 附加信息
///   - deviceID: 设备ID
///   - server: 连接的服务器ip/域名
-(void)postEvent:(EventTrackingType)type result:(NSNumber *)result message:(NSString *)message deviceID:(int)deviceID server:(nullable NSString *)server;

/// 事件埋点上传，实际只是讲事件入队等待上传
/// - Parameters:
///   - type: 事件类型
///   - result: 事件结果
///   - message: 附加信息
///   - userID: 用户ID
///   - deviceID: 设备ID
///   - network: 用户网络
///   - connect: 连接模式
///   - server: 连接的服务器ip/域名
///   - timestamp: 事件发生时间戳
-(void)track:(EventTrackingType)type result:(NSNumber *)result message:(NSString *)message userID:(NSNumber *)userID deviceID:(int)deviceID network:(int32_t)network connect:(int32_t)connect server:(nullable NSString *)server timestamp:(int64_t)timestamp;

/// 直接上传，不等待定时器
-(void)uploadEvents;

@end

NS_ASSUME_NONNULL_END
