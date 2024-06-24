//
//  AlarmConfigInfo.h
//  NVSDK
//
//  Created by caffe on 2019/2/22.
//  certified by caffe on 20190323
//  Copyright © 2019 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AlarmTimeModel.h"

typedef enum _iotc_propertie_a {
    ALARM_MAIN_SWITCH = 0,
    ALARM_SOUND_SWITCH,
    ALARM_MAIN_SOUND_SWITCH,
    ALARM_LANGUAGE_TYPE,
    ALARM_MT_SW,
    ALARM_MT_AREA,
    ALARM_TIMER_INFO,
    ALARM_PA_SW,
    ALARM_PA_ATTR
}iotc_properties_alarm;

NS_ASSUME_NONNULL_BEGIN

@interface AlarmConfigInfo : NSObject
@property (nonatomic, assign) int nResult;
/**
 需要设置的属性ID(新平台)
 */
@property (nonatomic,strong) NSArray *propertieID;

/**
 是否有语音控制
 */
@property (nonatomic, assign) BOOL hasSoundCtrl;
/**
 语音总开关
 */
@property (nonatomic, assign) BOOL bSoundMainSwitch;
/**
 报警语音提示开关
 */
@property (nonatomic, assign) BOOL bAlarmAudioSwitch;
/**
 是否支持设备语言切换
 */
@property (nonatomic, assign) BOOL nLanguageEnable;
/**
 语音提示语言类型
NV_LANGUAGE_CN         1000
NV_LANGUAGE_EN         1100
NV_LANGUAGE_ES         1101   // 西班牙语
NV_LANGUAGE_FR         1102   // 法语
NV_LANGUAGE_DE         1103;  // 德语
NV_LANGUAGE_IT         1104   // 意大利语
NV_LANGUAGE_JP         1105   // 日语
NV_LANGUAGE_KR         1106   // 韩语
NV_LANGUAGE_RU         1107   // 俄语
NV_LANGUAGE_PT         1108   // 葡萄牙语
NV_LANGUAGE_AR         1109   // 阿拉伯语
NV_LANGUAGE_FA         1110   // 波斯语
NV_LANGUAGE_PL         1111   // 波兰语
NV_LANGUAGE_ID         1112   // 印度尼西亚语
NV_LANGUAGE_TH         1113   // 泰语
NV_LANGUAGE_PH         1114   // 菲律宾语
NV_LANGUAGE_VI         1115;  // 越南语
 */
@property (nonatomic, assign) int nLanguage;
/**
 设备支持的语言类型集
 */
@property (nonatomic, assign) int nSupportLanguages;
/**
 是否有外部报警IO
 */
@property (nonatomic, assign) BOOL hasExternalIOCtrl;
/**
 外部报警IO工作模式
 */
@property (nonatomic, assign) int nIOMode;
/**
 是否有布防配置
 */
@property (nonatomic, assign) BOOL hasAlarmCtrl;
/**
 报警总开关
 */
@property (nonatomic, assign) BOOL bMainAlarmSwitch;
/**
 移动报警开关：0-关or不支持(v4)；1-开；10-关(v4)
 */
@property (nonatomic, assign) int bMotionAlarmSwitch;
/**
 PIR报警开关
 */
@property (nonatomic, assign) BOOL bPRIAlarmSwitch;
/**
 烟感报警开关 (deprecated)
 */
@property (nonatomic, assign) BOOL bSmokeAlarmSwitch;
/**
 时间区域使能
 */
@property(nonatomic,assign) BOOL canSetAlarmArea;
/**
 时间段数
 */
@property(nonatomic,assign) int alarmTimeCount;
/**
 时间段
 */
@property(nonatomic,strong) NSMutableArray *alarmTimeArr;
/**
 新平台每日时间段
 */
@property(nonatomic,strong) NSMutableDictionary *alarmTimeInfo;
/**
 报警区行数
 */
@property(nonatomic,assign) int alarmAreaRow;
/**
 报警区列数
 */
@property(nonatomic,assign) int alarmAreaColumn;
/**
 报警区域 row * column
 */
@property(nonatomic,strong) NSMutableArray *alarmAreaArr;
/**
 是否全天报警
 */
@property(nonatomic,assign) BOOL isAlldayAlarm;
/**
 AI使能
 */
@property(nonatomic,assign) BOOL AIEnble;
/**
 AI开关
 */
@property(nonatomic,assign) BOOL AISwitch;
/**
 高温度报警使能
 */
@property (nonatomic, assign) BOOL highTempPri;
/**
 高温报警开关
 */
@property (nonatomic, assign) BOOL highTempEnable;
/**
 高温报警提升音开关
 */
@property (nonatomic, assign) BOOL highTempAlarmSoundEnable;
/**
 高温报警温度
 */
@property (nonatomic, assign) int  highTemp;
/**
 低温报警使能
 */
@property (nonatomic, assign) BOOL lowTempPri;
/**
 低温报警开关
 */
@property (nonatomic, assign) BOOL lowTempEnable;
/**
 低温报警提升音开关
 */
@property (nonatomic, assign) BOOL lowTempAlarmSoundEnable;
/**
 低温报警温度
 */
@property (nonatomic, assign) int  lowTemp;
/**
 哭声检测使能
 */
@property (nonatomic, assign) BOOL cryDetectionPri;
/**
 哭声检测开关
 */
@property (nonatomic, assign) BOOL cryDetectionEnable;
/**
是否需要设置温控报警（设置参数）
 */
@property (nonatomic, assign) BOOL isShouldSaveTempAlarm;
/**
 移动侦测框开关 01：开 10：关 0不支持
 */
@property (nonatomic, assign) int motionAlarmFrame;
/**
 移动侦测警戒灯开关　00: 不支持　01:开　10:关
 */
@property (nonatomic ,assign) int motionDetectAlert_light_switch;
/**
主动报警开关
 */
@property (nonatomic, assign) BOOL positiveAlarmSwitch;
/**
主动报警消息
 */
@property (nonatomic, copy) NSString* positiveAlarmAttr;
/**
 主动报警消息字符串最大字节数 (base64编码前的字节数) （包括\0）
 */
@property (nonatomic, assign) int positiveAlarmContentMaxLength;
/**
 是否支持主动报警
 */
@property (nonatomic, assign) BOOL isSuppoerPositiveAlarm;

@end

NS_ASSUME_NONNULL_END
