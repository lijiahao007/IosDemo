//
//  NVDeviceConfigInfo.h
//  NVSDK
//
//  Created by caffe on 2019/2/21.
//  certified by weibin 20190325
//  Copyright © 2019 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "LoginHandle.h"
#import "NetworkConfigInfo.h"
#import "RecordConfigInfo.h"
#import "AlarmConfigInfo.h"
#import "TimeConfigInfo.h"
#import "VersionInfo.h"
#import "IPConfigInfo.h"
#import "ThermalConfigInfo.h"  //热成像 add by xys 20200609
#import "PTZCruiseConfigInfo.h"
#import "OtherConfigInfo.h"
#import "LightSettingInfo.h"
#import "TimeAlbumInfo.h"
#import "AIHumanAlarmInfo.h"
#import "PrivacyModeInfo.h"
#import "CPEConfigInfo.h"
typedef enum{
    INFO_NETWORK=1,
    INFO_RECORD=2,
    INFO_ALARM=3,
    INFO_VERSION=4,
    INFO_IP=5,
    INFO_DATETIME=6,
    INFO_SETTING =7,
    INFO_THERMAL = 8,  //热成像 add by xys 20200609
    INFO_PTZCRUISE = 9,    // 云台巡航
    INFO_LIGHT = 10, //白灯光设置
    INFO_PRIVACY = 11, //隐私权限设置
    INFO_AIALARM = 14, //AI人型检测报警
    INFO_TIEMALBUM = 15, //时光相册
    INFO_CPE = 16, //CPE信息
}INFO_TYPE;

NS_ASSUME_NONNULL_BEGIN

@interface NVDeviceConfigInfo : NSObject
@property (assign) int nResult;
@property (nonatomic, assign) int version;


@property(nonatomic,strong)NetworkConfigInfo *networkconfig;
@property(nonatomic,strong)RecordConfigInfo *recordConfig;
@property(nonatomic,strong)AlarmConfigInfo *alarmConfig;
@property(nonatomic,strong)TimeConfigInfo *timeConfig;
@property(nonatomic,strong)VersionInfo *versionInfo;
@property(nonatomic,strong)IPConfigInfo *iPConfig;
@property(nonatomic,strong)ThermalConfigInfo *thermalConfig;  //热成像 add by xys 20200609
@property(nonatomic,strong)PTZCruiseConfigInfo *cruiseConfig;
@property(nonatomic,strong)OtherConfigInfo *otherConfig;
@property(nonatomic,strong)LightSettingInfo *whiteLightConfig;//add by qin 20200718
@property(nonatomic,strong)AIHumanAlarmInfo *aiHumanAlarmConfig;
@property(nonatomic,strong)TimeAlbumInfo *timeAlbumConfig;
@property(nonatomic,strong)PrivacyModeInfo *privacyModeConfig;
@property(nonatomic,strong)CPEConfigInfo *cpeConfig;

-(BOOL)getDeviceConfigInfo:(NVDevice *)device handle:(LoginHandle *)lHandle;
-(BOOL)getDeviceConfigInfoForPreview:(NVDevice *)device handle:(LoginHandle *)lHandle;
-(void)cancel;
@end

NS_ASSUME_NONNULL_END
