//
//  OtherConfigInfo.h
//  NVSDK
//
//  Created by Yang on 2020/7/15.
//  Copyright © 2020 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum _iotc_propertie {
    AUDIO_DEV_AO_VOLUME = 0,
    PT_SPEED_H,
    PT_SPEED_V,
    FLOODLIGHT_SENSITIVITY,
    VIDEO_STANDARD
}iotc_properties_other;

NS_ASSUME_NONNULL_BEGIN

@interface OtherConfigInfo : NSObject

@property (assign) int nResult;
@property (nonatomic,strong) NSArray *propertieID;    //需要设置的属性ID(新平台)
@property (assign) int nSensitivity_PRI;    //PIR灵敏度 0：无效/不支持 01：低，02：中， 03： 高，10：关闭；100：关闭，101 - 110表示灵敏度1-10
@property (assign) int nBrightness;         //白光灯亮度
@property (assign) int nLightTime;          //亮灯时长
@property (assign) int nLightControl;       //光敏触发调节
@property (assign) int nMoveSensitivity;    //移动开关灯灵敏度
@property (assign) int nSpeechPlayerType;   //报警语音类型 1:default 2:custom
@property (assign) int resetEnable;         //01：支持远程复位 02：支持远程重启 04: 支持强制休眠(低功耗)（按位组合；如 7：支持远程复位和重启和支持强制休眠；（0：无效/不支持）
@property (assign) int rtspEnable;          //RTSP开关 01：开 10：关 开关+100 表示音频开启，+200表示音频关闭（0：无效/不支持）
@property (assign) int smokeEnable;         //烟感开关 01：开 10：关 （0：无效/不支持）
@property (assign) int rtspVideoType;       //RTSP 开启时设备使用的视频编码格式 0：不支持修改 1：H264 2:H265
@property (assign) int osdEnable;           //OSD显示开关 01：开 10：关 （0：无效/不支持）
@property (assign) int ptzVSensitivity;     //云台垂直方向的转速
@property (assign) int ptzHSensitivity;     //云台水平方向的转速
@property (nonatomic,assign) int ptzSensitivityMax;    //云台转速范围
@property (nonatomic,assign) int indicatorLightEnable; //指示灯开关 01：开 10：关 （0：无效/不支持）
@property (nonatomic,assign) int ledEnable;            //LED灯显示开关 01：开 10：关 （0：无效/不支持）

@property (assign) int videoStandard;      //是否支持P/N制设置，01：关闭，10：PAL 11：NTSC （0：无效/不支持
@property (assign) int powerSource; //电源类型 0：普通；1：长供电 2：低功耗电池 3：太阳能

@property (assign) int focalLengthEnable; // 镜头自动调焦使能 01：开 10：关 （0：无效/不支持）
@property (assign) int focalTime;       // 镜头自动调焦时长（单位秒）
@property (assign) int speakerVol;       // 喇叭音量 0：不支持 [1, 100]：音量百分比
@property (assign) int deviceQRInfo; //设备二维码信息 01：是 10：否 （0：无效/不支持）
@property (assign) NSString* deviceModelId; //设备modelId
@property (assign) int deviceConfigList; //设备配网选项列表
@property (assign) int deviceConfigSeleted; //配网首选项
@property (nonatomic,assign) int powerMode; //当前工作模式 0：无效/不支持 1：长供电模式 2：低功耗模式 4：智能供电模式 8:超长待机模式  16:电池不休眠模式
@property (nonatomic,assign) int powerModeEx; // 当前工作模式 0：无效/不支持 1:微功耗模式
@property (nonatomic,assign) BOOL isSetPowerMode; //是否是设置供电模式
@property (nonatomic,assign) BOOL timeEnable; //是否支持定时设置
@property(nonatomic,strong) NSMutableArray<AlarmTimeModel*> *nTimeArr; //智能供电时间段
@property (nonatomic,assign) int powerModeList; //支持工作模式列表； 0：无效/不支持 1：长供电模式 2：低功耗模式 4：智能供电模式 8:超长待机模式  16:电池不休眠模式   （时段外支持工作模式列表：32:低功耗模式 64：超长待机模式）
@property (nonatomic,assign) int powerModeListEx; //支持工作模式列表拓展； 0:无效/不支持 1:微功耗

@property (nonatomic,assign) int logUpload; // 01:是   10:否 （0:无效/不支持）

@property (nonatomic,assign) int HDR; // 宽动态 01:开  10:关 （0：无效/不支持）
@end

NS_ASSUME_NONNULL_END
