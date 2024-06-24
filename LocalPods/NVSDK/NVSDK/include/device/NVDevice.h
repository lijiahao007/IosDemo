//
//  LoginInfo.h
//  IMobilePlayer
//
//  Created by luo king on 11-12-17.
//  Copyright 2011 cctv. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define ADD_TYPE_HANDMAKE           10
#define ADD_TYPE_SEARCH_FROM_LAN    11
#define ADD_TYPE_SYNC_FROM_NET      12
#define ADD_TYPE_DEMO               13
#define ADD_TYPE_SHARE 14  //add by yang 20180315
#define ADD_TYPE_IOT_FROM_LAN    15
#define ADD_TYPE_IOS_FROM_WPS    32

#define EDIT_TPYE_ADD       100
#define EDIT_TPYE_MODIFY    101

#define ONLINE_STAT_READY   0
#define ONLINE_STAT_ON      100
#define ONLINE_STAT_OFF     101
#define ONLINE_STAT_ON_LAN  102
#define ONLINE_STAT_ON_WAN  103
#define ONLINE_STAT_PWD_ERR 104
#define ONLINE_STAT_UNKNOW  110

#define ONLINE_TIME_DURATION 60000
#define ALARM_EXPIRT_TIME 259200000

//nDeviceKind
#define DEVICE_KIND_UNKNOW         999     // 未知设备类型
#define DEVICE_KIND_ANCIENT        1000    // 所有v380现有设备（也可能是电池摄像机）
#define DEVICE_KIND_ANCIENTBATTERY 1001    // 使用现在v380架构的电池摄像机

//deviceType
#define DEVICE_TYPE_IPC_NROMAL         0       //0-普通IPC
#define DEVICE_TYPE_IPC_180            1       //1-180镜头IPC
#define DEVICE_TYPE_IPC_360            2       //2-360镜头IPC
#define DEVICE_TYPE_MESH               3       //3-自组网套装中继器
#define DEVICE_TYPE_STATION            4       //4-单品基站
#define DEVICE_TYPE_IPC_STATION        5       //5-单品基站的配套设备

@interface NVDevice : NSObject<NSCoding>
@property(nonatomic,assign) int deviceSoftwareUpdateStatus;//设备升级状态 0 未知 1 不升级 2需要提示升级


@property (assign) int nOnlineStatus;//
@property (assign) long long llOnlineTime;//
@property (assign) int isAlarmOn;//
@property (assign) BOOL isRecvAlarmMsg;

//add by luo20141103
@property (copy) NSString *strMRServer;
@property (assign) int nMRPort;
//end add by luo20141103

@property (assign) int nAlarmMsgCount;
@property (assign) long long lLastFreshTime;
@property (assign) long long lLastGetTime;
@property (assign) BOOL isSelect;
@property (assign) BOOL isInList;
@property (nonatomic,copy) NSString *strMacAddress;
@property (assign) int nID;
//@property (assign) int nDevID;
@property (assign) int nConfigID;//add by luo 20150409

@property (assign) int nAddType;
@property (nonatomic,copy) NSString *strName;
@property (nonatomic,copy) NSString *strServer;
@property (assign) int nPort;
@property (nonatomic,copy) NSString *strUsername;
@property (nonatomic,copy) NSString *strPassword;
@property (assign) BOOL isMRMode;
@property (nonatomic, copy) NSString *strDomain;
@property (nonatomic, retain) UIImage *imageFace;
@property (assign) int serverStatus;
@property(assign) int nDeviceType; //目前仅作用于云服务绑定，云服务绑定后返回设备类型10 是普通设备 20是4g低功耗设备 30是低成本4g

//add by xie yongsheng 20181023
@property (assign) int temporaryAlarmFlag;               //临时报警开关
@property (assign) long long temporaryAlarmTimestamp;        //临时报警开关的时间戳
@property (assign) int temporaryServiceID;               //临时云存储状态
@property (assign) long long temporaryServiceIDTimestamp;    //临时云存储状态的时间戳
//add end by xie yongsheng 20181023
@property (nonatomic,strong)NSNumber *tempServiceID;
@property (nonatomic, assign) long loginHandle;//added by weibin 20190401
@property (nonatomic, assign) int nVersion;//added by weibin 20190401

@property (nonatomic, assign) int nDeviceKind; //设备种类 add by xie yongsheng 20200311 上方有种类宏定义
@property (nonatomic,assign) int openCloudServerTipsTimestamp;
@property (nonatomic,assign) int nDeviceModel; // 设备的复合类型，详见DefineVars.h的复合类型定义，等同LoginHandle.dtype
@property (nonatomic,assign) int groupID;   // 设备的分组ID
@property (nonatomic,assign) int shareID;   // 分享设备的ID
@property (nonatomic,copy) NSString *shareFrom;   // 分享设备的人
@property (nonatomic,assign) int p2pId;   // p2p_id

//低功耗设备
/*  1 标准模式
 2 节电模式
 3 受限模式-超级省电，预览部分功能限制
 4 恢复模式-充电中
 5 低电量保护-关机
 */
@property (nonatomic,assign) int lowerPowerState;   // 低功耗设备状态
@property (nonatomic,assign) long lowerPowerWT;   // 预计充电时长
@property (nonatomic,strong) NSDictionary *eqDict;   // 电量预设值[ups超级节能模式电量 ps节能模式电量 complete全功能模式电量]

@property (nonatomic,copy) NSString *standbyDomain; //国际连接备用域名

//新iot平台重构
@property (nonatomic,copy) NSString *accessToken;
@property (nonatomic,copy) NSString *publicKey;
@property (nonatomic,copy) NSString *clientPublicKey;
@property (nonatomic,strong) NSData *clientPrivateKey;
@property (nonatomic,assign) int deviceVersion;//设备类型，用于区分新设备(2)和旧设备(1)
@property (nonatomic,copy) NSString *modelId;
@property (nonatomic, assign) int spid; // subProductId
@property (nonatomic ,assign) long long permission; //分享权限
@property (nonatomic ,assign) long updateID; //固件更新

@property (nonatomic, assign) int supportConfigList; // 支持的配网方式。


@property (nonatomic,assign) int tlvType;   // 设备能力 0是不支持,7是支持智能关联,15是支持智能关联和时光回溯
-(void) setDevID:(int)nDeviceID;
-(int) NDevID;

-(BOOL)isMatch:(NVDevice *)info;

-(BOOL)isMatch:(int)devID username:(NSString *)username password:(NSString *)password;

-(void)copyDeviceInfo:(NVDevice *)info;
@end
