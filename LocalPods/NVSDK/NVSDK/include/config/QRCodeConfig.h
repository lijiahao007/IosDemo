//
//  QRCodeConfig.h
//  NVSDK
//
//  Created by admin on 2022/2/26.
//  Copyright © 2022 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#define kDeviceID           @"deviceID"         //设备ID
#define kModel              @"model"            //设备类型
#define kFirstConnect       @"firstConnect"     //首选配网方式
#define kSecondConnect      @"secondConnect"    //备选配网方式
#define kConnectType        @"connectType"      //可支持的配网方式
#define kFactoryId          @"factoryId"        //工厂ID（可为空）
#define kDate               @"date"             //时间（可为空）
#define kDeviceVer          @"version"          //设备版本，新平台/旧设备
#define kDeviceBindToken    @"token"            //新平台绑定token
#define kDeviceFastPin      @"fastpin"          //新平台fastPin
#define kError              @"error"            //错误信息
#define kSpid               @"spid"             //subProductId

@interface QRCodeConfig : NSObject
//配网方式
typedef enum : NSUInteger {
    DeviceConnectType_UNKNOW    = -1,
    DeviceConnectType_ERR       = 0,
    DeviceConnectType_AP        = 1,
    DeviceConnectType_QR        = 2,
    DeviceConnectType_SMARTLINK = 4,
    DeviceConnectType_4G        = 8,
    DeviceConnectType_5G        = 16,
    DeviceConnectType_WPS       = 32,
    DeviceConnectType_BLUETOOTH = 64,
    DeviceConnectType_Tone      = 128, // 声波配网
    DeviceConnectType_PinCode   = 256,
} DeviceConnectType;

//解析设备二维码
-(NSMutableDictionary*)parseQRCode:(NSString*)code;
-(NSMutableDictionary*)parseQRCodeIOT:(NSString*)code;

//生成用于设备扫描的二维码字符串
-(NSString*)createQRCodeWithSSID:(NSString*)ssid password:(NSString*)password random:(int)random token:(NSString*)token;

//pingCode
-(int)pingCodeRequestAction:(int)action;
+(int)pingCodeAndFastPinRequestAction:(int)action fastPin:(NSString *)fastPin pincode:(int)code bindinfo:(NSString*)bindinfo device:(NVDevice*)device;

-(int) sendFastPinAndPincodeInLanAction:(int)action fastPin:(NSString *)fastPin pincode:(int)pincode clicode:(int)clicode bindInfo:(NSString*)bindInfo;
@end

NS_ASSUME_NONNULL_END
