//
//  NVDeviceConfigHelper.h
//  NVSDK
//
//  Created by caffe on 2019/2/21.
//  certified by caffe 20190325
//  Copyright © 2019 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>


#import "AccountConfigInfo.h"
#import "RecordConfigInfo.h"
#import "VersionInfo.h"
#import "TimeConfigInfo.h"
#import "AlarmConfigInfo.h"
#import "NetworkConfigInfo.h"
#import "DeviceUpdateInfo.h"
#import "IPConfigInfo.h"
#import "OtherConfigInfo.h"
#import "ThermalConfigInfo.h"
#import "PTZCruiseConfigInfo.h"
#import "TimeAlbumInfo.h"
#import "AIHumanAlarmInfo.h"
#import "CalibrationInfo.h"
#import "TimeAlbumInfo.h"
#import "PrivacyModeInfo.h"
@class NVDevice;
@class LoginHandle;
NS_ASSUME_NONNULL_BEGIN

@interface NVDeviceConfigHelper : NSObject

+(AccountConfigInfo *)getAccountConfigInfo:(NVDevice *)device handle:(LoginHandle *)lHandle;
+(int)setAcountConfigInfo:(NVDevice *)device account:(AccountConfigInfo *)account handle:(LoginHandle *)lHandle;

+(RecordConfigInfo *)getRecordConfigInfo:(NVDevice *)device handle:(LoginHandle *)lHandle;
+(int)setRecordConfigInfo:(NVDevice *)device account:(RecordConfigInfo *)info handle:(LoginHandle *)lHandle;
+(int)startFormatSDCard:(NVDevice *)device handle:(LoginHandle *)lHandle;

+(VersionInfo *)getVersionInfo:(NVDevice *)device handle:(LoginHandle *)lHandle;
+(DeviceUpdateInfo *)getDeviceVersionInfo:(NVDevice *)device handle:(LoginHandle *)lHandle;
+(int)startUpdateDeviceVersion:(NVDevice *)device handle:(LoginHandle *)lHandle;

+(TimeConfigInfo *)getTimeConfigInfo:(NVDevice *)device handle:(LoginHandle *)lHandle;
+(int)setTimeConfigInfo:(NVDevice *)device account:(TimeConfigInfo *)info handle:(LoginHandle *)lHandle;

+(AlarmConfigInfo *)getAlarmConfigInfo:(NVDevice *)device handle:(LoginHandle *)lHandle;
+(int)setAlarmConfigInfo:(NVDevice *)device account:(AlarmConfigInfo *)info handle:(LoginHandle *)lHandle;

+(int)setOneKeyAlarm:(NVDevice *)device isAlarm:(BOOL)isAlarm handle:(LoginHandle *)lHandle;

+(NetworkConfigInfo *)getNetworkConfigInfo:(NVDevice *)device handle:(LoginHandle *)lHandle;
+(int)setNetworkConfigInfo:(NVDevice *)device account:(NetworkConfigInfo *)info handle:(LoginHandle *)lHandle;
+(IPConfigInfo *)getIPConfigInfo:(NVDevice *)device handle:(LoginHandle *)lHandle;
+(int)setIPConfigInfo:(NVDevice *)device info:(IPConfigInfo *)info handle:(LoginHandle *)lHandle;
+(NSArray *)getVisibleWifiListFromDevice:(NVDevice *)device handle:(LoginHandle *)lHandle;

+(OtherConfigInfo *)getOtherConfigInfo:(NVDevice *)device handle:(LoginHandle *)lHandle;
+(int)setOtherConfigInfo:(NVDevice *)device account:(OtherConfigInfo *)info handle:(LoginHandle *)lHandle;

+(PTZCruiseConfigInfo*)getPTZXCruiseConfigInfo:(NVDevice*)device handle:(LoginHandle*)lHandle;
+(int)setPTZXCruiseConfigInfo:(NVDevice*)device info:(PTZCruiseConfigInfo*)info handle:(LoginHandle*)lHandle action:(int)action;

+(int)setAIHumanAlarmConfigInfo:(NVDevice *)device account:(AIHumanAlarmInfo *)info handle:(LoginHandle *)lHandle;

+(int)setTimeAlbumConfigInfo:(NVDevice *)device account:(TimeAlbumInfo *)info handle:(LoginHandle *)lHandle;

//action=1 获取开关状态 action=2 获取全部镜头信息
+(CalibrationInfo* )getCalibrationConfig:(NVDevice *)device action:(int)action handle:(LoginHandle *)lHandle;
+(int)setCalibrationConfig:(NVDevice *)device handle:(LoginHandle *)lHandle config:(CalibrationInfo *)info;

+(int)SetAlarmAudio:(NVDevice *)device fileType:(int)fType path:(NSString *)pathStr alarmType:(int)alarmType handle:(LoginHandle *)lHandle;
+(void)initRecord;
+(BOOL)startRecordAlarmAudio:(NSString*)pathStr;
+(void)stopRecordAlarmAudio;
+(void)preparePlayAudio:(NSString *)pathStr;
+(void)playAudio;
+(void)stopPlayAudiio;

+(int)setThermalInfo:(NVDevice *)device info:(ThermalConfigInfo *)info handle:(LoginHandle *)lHandle;

+(int)SetDeviceLightConfig:(NVDevice *)device defaultAction:(int)defaultAction timingAction:(int)timingAction startTime:(NSString *)startTime endTime:(NSString *)endTime mainSwitch:(int)mainSwitch motionDetectionSwitch:(int)motionDetectionSwitch humanDetectionSwitch:(int)humanDetectionSwitch indicatorSwitch:(int)indicatorSwitch handle:(LoginHandle *)lHandle;

+(int)setDeviceFocalConfig:(NVDevice *)device handle:(LoginHandle *)lHandle;

+(int)quickReply:(NVDevice *)device responseId:(int)responseId handle:(LoginHandle *)lHandle;

+(int)setDevicePrivacyConfig:(NVDevice *)device timerArr:(NSMutableArray *)timerArray enabled:(int)enabled handle:(LoginHandle *)lHandle;

//云台自动校准
+(int)ptzAutomaticCalibrationWithHandle:(LoginHandle *)lHandle;
//查询云台自检状态:10：不支持云台；11：自检中；12：自检完成；13：自检失败,其他：连接失败
+(int)checkPTZAutomaticDetection:(LoginHandle *)lHandle device:(NVDevice*)device;
//枪球联动镜头校准获取
+(CalibrationInfo* )getLinkageCalibrationConfig:(NVDevice *)device handle:(LoginHandle *)lHandle;
+(int)setLinkageCalibrationConfig:(NVDevice *)device handle:(LoginHandle *)lHandle config:(CalibrationInfo *)info;
/*
 进入/退出枪球联动校准设置（用于设备临时关闭移动跟踪等云台相关功能）
 action 01：进入；10：退出
 exitTimeout 退出联动校准超时时间，单位: 秒
 */
+(int)enterLinkageConfig:(NVDevice *)device handle:(LoginHandle *)lHandle action:(int)action exitTimeout:(int)exitTimeout;

+(void)cancelConfig;

//- 新平台设备复位(1)/重启(2)
+(int)setDeviceBasicAbility:(NVDevice *)device action:(int)action;
// - 新平台局域网lanpa修改安全密码
+(int)setDeviceLanPassword:(NVDevice*)device newPassword:(NSString *)password;
@end

NS_ASSUME_NONNULL_END
