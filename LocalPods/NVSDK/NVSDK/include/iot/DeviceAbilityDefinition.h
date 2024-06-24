//
//  DeviceAbilityDefinition.h
//  NVSDK
//
//  Created by 547 on 2022/11/17.
//  Copyright © 2022 macrovideo. All rights reserved.
//

#ifndef DeviceAbilityDefinition_h
#define DeviceAbilityDefinition_h

#define BMPC(N) (1UL<<(N-1))  ///< BMPC值转换

#pragma mark -----设备能力定义（所有能力位值宽度最大32bit）-----
/**************************************
 * 1. 注意！！！只能增加，且顺序不能改变！
 *
 * 2. bmpc定义，为bitmap位图定义，
 *    定义新增时注意不要超过范围
 *
 * 3. 非bmpc定义，则为普通枚举
**************************************/
/** 视频流能力集 */
typedef enum _abl_video_bmpc32
{
    ABL_VIDEO_NOT_SUPPORT          = 0x00,
    ABL_VIDEO_CAPTURE              = BMPC(1),  ///< 视频采集
    ABL_VIDEO_DISPLAY              = BMPC(2),  ///< 视频播放
    ABL_VIDEO_ENCODER_CHANGE       = BMPC(3),  ///< 编码类型切换
    ABL_VIDEO_THERMAL_IMAGE        = BMPC(4),  ///< 热成像
}abl_video_bmpc32_e;

/** 音频流能力集 */
typedef enum _abl_audio_bmpc32
{
    ABL_AUDIO_NOT_SUPPORT          = 0x00,
    ABL_AUDIO_CAPTURE              = BMPC(1),  ///< 音频采集
    ABL_AUDIO_PLAY                 = BMPC(2),  ///< 音频播放(对讲)
    ABL_AUDIO_CAPTURE_VOLUME       = BMPC(3),  ///< 采集音量调节
    ABL_AUDIO_PLAY_VOLUME          = BMPC(4),  ///< 播放音量调节(对讲)
    ABL_AUDIO_ENCODER_CHANGE       = BMPC(5),  ///< 编码类型切换
}abl_audio_bmpc32_e;

/** 视频流编解码能力 */
typedef enum _abl_video_codec_bmpc32
{
    ABL_VIDEO_CODEC_NOT_SUPPORT    = 0x00,
    ABL_VIDEO_CODEC_MJPEG          = BMPC(1),
    ABL_VIDEO_CODEC_H264           = BMPC(2),
    ABL_VIDEO_CODEC_H265           = BMPC(3),
}abl_video_codec_bmpc32_e;

/** 音频流编解码能力 */
typedef enum _abl_audio_codec_bmpc32
{
    ABL_AUDIO_CODEC_NOT_SUPPORT    = 0x00,
    ABL_AUDIO_CODEC_PCM            = BMPC(1),
    ABL_AUDIO_CODEC_ADPCM          = BMPC(2),
    ABL_AUDIO_CODEC_ADTS_AAC       = BMPC(3),
    ABL_AUDIO_CODEC_G711A          = BMPC(4),
    ABL_AUDIO_CODEC_G711U          = BMPC(5),
}abl_audio_codec_bmpc32_e;

/** 视频质量能力 */
typedef enum _abl_video_quality_bmpc32
{
    ABL_VIDEO_QUAL_NOT_SUPPORT     = 0x00,
    ABL_VIDEO_QUAL_SD              = BMPC(1),
    ABL_VIDEO_QUAL_HD              = BMPC(2),
    ABL_VIDEO_QUAL_FHD             = BMPC(3),
}abl_video_quality_bmpc32_e;

/** 云台控制能力集 */
typedef enum _abl_pt_ctrl_bmpc32
{
    ABL_PT_CTRL_NOT_SUPPORT        = 0x00,
    ABL_PT_CTRL_HORIZONTAL         = BMPC(1),  ///< 水平电机
    ABL_PT_CTRL_VERTICAL           = BMPC(2),  ///< 垂直电机
    ABL_PT_CTRL_SPEED              = BMPC(3),  ///< 转速设置
    ABL_PT_CTRL_OBJTRACK           = BMPC(4),  ///< 运动跟踪
    ABL_PT_CTRL_RECAL              = BMPC(5),  ///< 手动校准
    ABL_PT_CTRL_AUTO_RECAL         = BMPC(6),  ///< 自动校准
}abl_pt_ctrl_bmpc32_e;

/** 镜头能力集 */
typedef enum _abl_lens_bmpc32
{
    ABL_LENS_NORMAL                = 0x00,     ///< 普通
    ABL_LENS_WALL_PANO             = BMPC(1),  ///< 挂壁(180°)全景
    ABL_LENS_CEILING_PANO          = BMPC(2),  ///< 吸顶(360°)全景
}abl_lens_bmpc32_e;

/** 变焦变倍能力集 */
typedef enum _abl_zoom_ctrl_bmpc32
{
    ABL_ZOOM_CTRL_NOT_SUPPORT      = 0x00,
    ABL_ZOOM_CTRL_SUPPORT          = BMPC(1), ///< 变倍控制
    ABL_ZOOM_CTRL_REFOCUS          = BMPC(2), ///< 自动(校准)对焦
    ABL_ZOOM_CTRL_MANUAL_FOCUS     = BMPC(3), ///< 手动调焦
}abl_zoom_ctrl_bmpc32_e;

/** 图像旋转能力 */
typedef enum _abl_cam_rotate_bmpc32
{
    ABL_CAM_ROTATE_NOT_SUPPORT     = 0x00,
    ABL_CAM_ROTATE_FLIP_AND_MIRROR = BMPC(1), ///< 镜像翻转（非独立操作）
    ABL_CAM_ROTATE_MIRROR          = BMPC(2), ///< 镜像
    ABL_CAM_ROTATE_ANGLE           = BMPC(3), ///< 角度（固定角度）
}abl_cam_rotate_bmpc32_e;

/** 灯能力(通用定义) */
typedef enum _abl_light_ctrl_bmpc32
{
    ABL_LIGHT_CTRL_NOT_SUPPORT     = 0x00,
    ABL_LIGHT_CTRL_SWITCH          = BMPC(1), ///< 手动开关（包含自动）
    ABL_LIGHT_CTRL_SCHEDULE        = BMPC(2), ///< 定时设置
}abl_light_ctrl_bmpc32_e;

/** 夜视能力集 */
typedef enum _abl_nightvision_bmpc32
{
    ABL_NIGHTVISION_NOT_SUPPORT    = 0x00,
    ABL_NIGHTVISION_NORMAL         = BMPC(1), ///< 支持普通夜视(自动)
    ABL_NIGHTVISION_NORMAL_MANUAL  = BMPC(2), ///< 支持普通夜视(手动：开/关)
    ABL_NIGHTVISION_COLOR          = BMPC(3), ///< 支持全彩夜视(自动)
    ABL_NIGHTVISION_COLOR_MANUAL   = BMPC(4), ///< 支持全彩夜视(手动：开/关)
}abl_nightvision_bmpc32_e;

/** 图像调节能力 */
typedef enum _abl_isp_cfg_bmpc32
{
    ABL_ISP_CFG_NOT_SUPPORT        = 0x00,
    ABL_ISP_ANTI_FLICKER           = BMPC(1), ///< 抗频闪
}abl_isp_cfg_bmpc32_e;

/** OSD能力 */
typedef enum _abl_osd_cfg_bmpc32
{
    ABL_OSD_NOT_SUPPORT           = 0x00,
    ABL_OSD_DATE                  = BMPC(1),  ///< 日期OSD(开关)
    ABL_OSD_TEXT                  = BMPC(2),  ///< 文本OSD(开关、修改)
    ABL_OSD_LOGO                  = BMPC(3),  ///< 图片OSD(开关、修改)
    ABL_OSD_POSITION              = BMPC(4),  ///< OSD位置修改
}abl_osd_cfg_bmpc32_e;

/** 网络接口 */
typedef enum _abl_network_if_bmpc32
{
    ABL_NETWORK_IF_NOT_SUPPORT     = 0x00,
    ABL_NETWORK_IF_WIFI_2_4G       = BMPC(1), ///< WiFi-2.4G
    ABL_NETWORK_IF_WIFI_5_8G       = BMPC(2), ///< WiFi-5.8G
    ABL_NETWORK_IF_ETHERNET        = BMPC(3), ///< 以太网口
    ABL_NETWORK_IF_LTE             = BMPC(4), ///< 移动网络
    ABL_NETWORK_IF_BLE             = BMPC(5), ///< 蓝牙
}abl_network_if_bmpc32_e;

/** 绑定方式 */
typedef enum _abl_binding_bmpc32
{
    ABL_BINDING_NOT_SUPPORT        = 0x00,
    ABL_BINDING_QRCODE             = BMPC(1), ///< 二维码绑定
    ABL_BINDING_PINCODE            = BMPC(2), ///< PINCODE绑定
    ABL_BINDING_WPS                = BMPC(3), ///< 物理验证绑定
}abl_binding_bmpc32_e;

/** 网络配置能力 */
typedef enum _abl_network_cfg_bmpc32
{
    ABL_NETWORK_NOT_SUPPORT        = 0x00,
    ABL_NETWORK_ROUTER_CFG         = BMPC(1), ///< 路由配置(WiFi/...)
    ABL_NETWORK_STATIC_IP          = BMPC(2), ///< 静态IP(WiFi/Ethernet/...)
}abl_network_cfg_bmpc32_e;

/** 范围框类能力 */
typedef enum _abl_zone
{
    ABL_ZONE_NOT_SUPPORT           = 0,
    ABL_ZONE_RECTANGLE             = 1,       ///< 矩形
    ABL_ZONE_RESERVE               = 2,       ///< (保留)
    ABL_ZONE_N_LINE_MIN            = 3,       ///< >=3表示支持不规则多边形
    ABL_ZONE_N_LINE_MAX            = 255,
}abl_zone_e;

/** 灵敏度类能力 */
typedef enum _abl_sensitivity
{
    ABL_SENS_NOT_SUPPORT           = 0,
    ABL_SENS_RESERVE               = 1,       ///< (保留)
    ABL_SENS_STANDARD_2            = 2,       ///< <=3: 标准制（2=高/1=低）
    ABL_SENS_STANDARD_3            = 3,       ///< <=3: 标准制（3=高/2=中/1=低）
    ABL_SENS_LEVEL_MAX             = 255,     ///< >=4: 等级制（1 ~ max）
}abl_sensitivity_e;

/** 槽类（线/点/...）能力 */
typedef enum _abl_slot
{
    ABL_SLOT_NOT_SUPPORT           = 0,
    ABL_SLOT_N_MAX                 = 255,     ///< 最大数
}abl_slot_e;

/** 定时类能力 */
typedef enum _abl_schedule
{
    ABL_SCHE_NOT_SUPPORT           = 0,
    ABL_SCHE_SCHEDULE_MAX          = 255,     ///< 最大计划数
}abl_schedule_e;

/** 倍率类能力（小数类型数据，按照实际规定使用整数表示）
 * 如小数位2能力： 10.12 <=> 1012
 */
typedef enum _abl_ratio
{
    ABL_RATIO_NOT_SUPPORT          = 0,
    ABL_RATIO_MAX                  = UINT_MAX, ///< 最大倍率数
}abl_ratio_e;

/** 报警配置能力 */
typedef enum _abl_alert_cfg_bmpc32
{
    ABL_ALERT_CFG_NOT_SUPPORT      = 0x00,
    ABL_ALERT_CFG_ARMING           = BMPC(1), ///< 布撤防
    ABL_ALERT_CFG_SCHEDULE         = BMPC(2), ///< 报警时间段
    ABL_ALERT_CFG_MANUALLY_ALERT   = BMPC(3), ///< 手动报警
    ABL_ALERT_CFG_CUSTOM_SOUND     = BMPC(4), ///< 自定义报警音
    ABL_ALERT_CFG_SOUND_MUSIC_LIST = BMPC(5), ///< 报警音音乐列表关联
    ABL_ALERT_CFG_WARNING_LIGHT    = BMPC(6), ///< 报警灯
}abl_alert_cfg_bmpc32_e;

/** 报警侦测能力 */
typedef enum _abl_detect_cfg_bmpc32
{
    ABL_ALERT_EVT_NOT_SUPPORT      = 0,
    ABL_ALERT_EVT_MOTION           = 1,       ///< 运动事件
    ABL_ALERT_EVT_STAY             = 2,       ///< 逗留事件
    ABL_ALERT_EVT_EFENCE_ENTER     = 3,       ///< 区域入侵事件
    ABL_ALERT_EVT_EFENCE_EXIT      = 4,       ///< 区域离开事件
    ABL_ALERT_EVT_LINE_CROSSING    = 5,       ///< 越线事件
    ABL_ALERT_EVT_PERCETION        = 6,       ///< 感知事件（一般用于对象来源为特定传感器）
    ABL_ALERT_EVT_BABYCRY          = 7,       ///< 哭声事件
}abl_detect_bmpc32_e;

typedef enum _abl_alert_event_bmcp32
{
    ABL_ALERT_DETECT_NOT_SUPPORT   = 0,
    ABL_ALERT_DETECT_MOTION        = BMPC(1), ///< 运动侦测
    ABL_ALERT_DETECT_STAY          = BMPC(2), ///< 逗留侦测
    ABL_ALERT_DETECT_EFENCE        = BMPC(3), ///< 电子围栏
    ABL_ALERT_DETECT_LINE_CROSSING = BMPC(4), ///< 越线侦测
    ABL_ALERT_DETECT_BABYCRY       = BMPC(5), ///< 哭声检测
}abl_alert_detect_bmcp32_e;
/** 报警事件属性能力 */
typedef enum _abl_alert_event_attribute_bmpc32
{
    ABL_ALERT_EVT_ATTR_NOT_SUPPORT  = 0x00,
    ABL_ALERT_EVT_ATTR_SENSITIVITY  = BMPC(1), ///< 灵敏度
    ABL_ALERT_EVT_ATTR_WARNING_LIGHT= BMPC(2), ///< 警示灯
    ABL_ALERT_EVT_ATTR_SOUND        = BMPC(3), ///< 报警音
}abl_alert_evt_bmpc32_e;

/** 报警对象 */
typedef enum _abl_alert_object_id
{
    ABL_ALERT_OBJ_INVALID          = 0, ///< 无效
    ABL_ALERT_OBJ_ANYMOUS          = 1, ///< 其他未细分对象
    ABL_ALERT_OBJ_PERSON           = 2, ///< 人形
    ABL_ALERT_OBJ_SMOKE            = 3, ///< 烟雾
}abl_alert_detect_oid_e;
typedef enum _abl_alert_object_bmcp32
{
    ABL_ALERT_DETECT_OBJ_INVALID   = 0,
    ABL_ALERT_DETECT_OBJ_ANYMOUS   = BMPC(ABL_ALERT_OBJ_ANYMOUS), ///< 未细分对象
    ABL_ALERT_DETECT_OBJ_PERSON    = BMPC(ABL_ALERT_OBJ_PERSON),  ///< 人形
    ABL_ALERT_DETECT_OBJ_SMOKE     = BMPC(ABL_ALERT_OBJ_SMOKE),   ///< 烟雾
}abl_alert_object_bmcp32_e;
/** 报警对象能力 */
typedef enum _abl_alert_object_attribute_bmpc32
{
    ABL_ALERT_OBJ_ATTR_NOT_SUPPORT      = 0x00,
    ABL_ALERT_OBJ_ATTR_SENSITIVITY      = BMPC(1), ///< 置信度
    ABL_ALERT_OBJ_ATTR_THRESHOLD        = BMPC(2), ///< 触发阈值（感知类或数值类对象）/检测大小限制（识别类对象）
    ABL_ALERT_OBJ_ATTR_WARNING_LIGHT    = BMPC(3), ///< 警示灯
    ABL_ALERT_OBJ_ATTR_SOUND            = BMPC(4), ///< 报警音
    ABL_ALERT_OBJ_ATTR_TAG_DRAW         = BMPC(5), ///< 标签绘制（画框/标签）
    ABL_ALERT_OBJ_ATTR_PERCEPTION_ONLY  = BMPC(6), /**  仅支持感知（无法结合图像定位）
                                                        如:烟雾这类对象，可以从图像识别，也可以从传感器感知
                                                        这时候就需要用到此能力明确对象来源；
                                                        方便标识图像识别类事件无法关联此对象）*/
}abl_alert_obj_attr_bmpc32_e;

/** 报警过滤器（由事件与对象并列构成） */
typedef enum _abl_alert_filter
{
    ABL_ALERT_FILTER_INVALID       = 0,
    ABL_ALERT_FILTER_MOTION,          ///< 移动
    ABL_ALERT_FILTER_STAY,            ///< 逗留
    ABL_ALERT_FILTER_EFENCE_ENTER,    ///< 区域入侵
    ABL_ALERT_FILTER_EFENCE_EXIT,     ///< 区域离开
    ABL_ALERT_FILTER_LINE_CROSSING,   ///< 越线
    ABL_ALERT_FILTER_BABYCRY,         ///< 婴儿哭声
    ABL_ALERT_FILTER_PERSON,          ///< 人形
    ABL_ALERT_FILTER_SMOKE,           ///< 烟雾
    ///< ...可扩展
    ABL_ALERT_FILTER_NUM,
    ABL_ALERT_FILTER_MAX           = 28,    ///< 目前模块最大支持28种过滤器类型
}abl_alert_filter_e;

/** 活动状态 */
typedef enum _abl_status_bmpc32
{
    ABL_STATUS_NOT_SUPPORT         = 0,
    ABL_STATUS_ACTIVE              = BMPC(1), ///< 活跃
    ABL_STATUS_STAY                = BMPC(2), ///< 停留
    ABL_STATUS_ENTER               = BMPC(3), ///< 进入
    ABL_STATUS_EXIT                = BMPC(4), ///< 退出
}abl_status_bmpc32_e;

/** 报警音能力 */
typedef enum _abl_alert_sound_bmpc32
{
    ABL_ALERT_SOUND_NOT_SUPPORT    = 0,
    ABL_ALERT_SOUND_BASIC          = BMPC(1), ///< 支持提示音（开关）
    ABL_ALERT_SOUND_CUSTOM         = BMPC(2), ///< 自定义提示音
    ABL_ALERT_SOUND_MUSIC_LIST     = BMPC(3), ///< 音乐列表关联
}abl_alert_sound_bmpc32_e;

/** 报警灯能力 */
typedef enum _abl_alert_wl_bmpc32
{
    ABL_ALERT_WL_NOT_SUPPORT       = 0,
    ABL_ALERT_WL_BASIC             = BMPC(1), ///< 支持报警灯（开关）
}abl_alert_wl_bmpc32_e;

/** 录像能力 */
typedef enum _abl_record_bmpc32
{
    ABL_RECORD_TYPE_NOT_SUPPORT    = 0x00,
    ABL_RECORD_TYPE_SPONTANEOUS    = BMPC(1), ///< 连续录像
    ABL_RECORD_TYPE_EVENT          = BMPC(2), ///< 事件录像
    ABL_RECORD_TYPE_TLV            = BMPC(3), ///< 浓缩录像
    ///< ...
    ABL_RECORD_CFG_WITH_AUDIO      = BMPC(8), ///< 录像音频
}abl_record_bmpc32_e;

/** 存储卡能力 */
typedef enum _abl_sdcard_bmpc32
{
    ABL_SDCARD_NOT_SUPPORT         = 0x00,
    ABL_SDCARD_CAPACITY            = BMPC(1), ///< 存储卡容量
    ABL_SDCARD_FORMAT              = BMPC(2), ///< 格式化
    ABL_SDCARD_MANUALLY_CTRL       = BMPC(3), ///< 手动操作(挂载/弹出)
}abl_sdcard_bmpc32_e;

/** 提示音能力 */
typedef enum _abl_prompt_bmpc32
{
    ABL_PROMPT_NOT_SUPPORT         = 0x00,
    ABL_PROMPT_NORMAL              = BMPC(1), ///< 普通提示音(含开关)
    ABL_PROMPT_ALERT               = BMPC(2), ///< 报警提示音(含开关)
    ABL_PROMPT_CUSTOMISE           = BMPC(3), ///< 自定义提示音
    ABL_PROMPT_LANGUAGE            = BMPC(4), ///< 语言切换
    ABL_PROMPT_PRESET_MUSIC_LIST   = BMPC(5), ///< 预设音频列表(服务器音频, 同时可应用于报警音音乐列表关联)
}abl_prompt_bmpc32_e;

/** 扩展协议能力 */
typedef enum _abl_extprotocol_bmpc32
{
    ABL_EXTPROT_NOT_SUPPORT        = 0x00,
    ABL_EXTPROT_ONVIF              = BMPC(1), ///< ONVIF协议
}abl_extprotocol_bmpc32_e;

/** 设备维护能力 */
typedef enum _abl_maintenance_bmpc32
{
    ABL_MAINT_NOT_SUPPORT          = 0x00,
    ABL_MAINT_REBOOT               = BMPC(1), ///< 远程重启
    ABL_MAINT_AUTO_REBOOT          = BMPC(2), ///< 自动重启
}abl_maintenance_bmpc32_e;

#pragma mark -----设备能力集-----
/** 流能力集(data::stream) */
typedef enum _dev_stream_ability_code
{
    MVS_DSTREAM_ABLC_VIDEO,         ///< 视频流      [abl_video_bmpc32_e]
    MVS_DSTREAM_ABLC_VIDEO_ENCODER, ///< 视频编码支持 [abl_video_codec_bmpc32_e]
    MVS_DSTREAM_ABLC_VIDEO_DECODER, ///< 视频解码支持 [abl_video_codec_bmpc32_e]
    MVS_DSTREAM_ABLC_AUDIO,         ///< 音频流      [abl_audio_bmpc32_e]
    MVS_DSTREAM_ABLC_AUDIO_ENCODER, ///< 音频编码支持 [abl_audio_codec_bmpc32_e]
    MVS_DSTREAM_ABLC_AUDIO_DECODER, ///< 音频解码支持 [abl_audio_codec_bmpc32_e]
    MVS_DSTREAM_ABLC_VIDEO_QUALITY, ///< 视频质量支持 [abl_video_quality_bmpc32_e]

    MVS_DSTREAM_ABLC_NUM,
}mvs_dstream_ablc_e;

/** 图像能力集(data::image) */
typedef enum _dev_image_ability_code
{
    MVS_DIMAGE_ABLC_CAM_ROTATE,     ///< 图像旋转   [abl_cam_rotate_bmpc32_e]
    MVS_DIMAGE_ABLC_ISP,            ///< 图像设置   [abl_isp_cfg_bmpc32_e]
    MVS_DIMAGE_ABLC_NIGHTVISION,    ///< 夜视能力   [abl_nightvision_bmpc32_e]
    MVS_DIMAGE_ABLC_OSD,            ///< 水印能力   [abl_osd_cfg_bmpc32_e]

    MVS_DIMAGE_ABLC_NUM,
}mvs_dimage_ablc_e;

/** 控制能力集(data::ctrl) */
typedef enum _dev_ctrl_ability_code
{
    MVS_DCTRL_ABLC_PT_CTRL,         ///< 云台控制   [abl_pt_ctrl_bmpc32_e]
    MVS_DCTRL_ABLC_PT_PRESETS,      ///< 预置位     [abl_slot_e]
    MVS_DCTRL_ABLC_PT_AUTO_CRUISE,  ///< 自动巡航   [abl_schedule_e]（多点巡航路线）
    MVS_DCTRL_ABLC_PT_CRUISE_SCHE,  ///< 定时巡航   [abl_schedule_e]（定点定时巡航）
    MVS_DCTRL_ABLC_ZOOM,            ///< 变倍变焦   [abl_zoom_ctrl_bmpc32_e]
    MVS_DCTRL_ABLC_ZOOM_RATIO_MAX,  ///< 最大变倍率 [abl_ratio_e]（小数2位）
    MVS_DCTRL_ABLC_ZOOM_RATIO_STEP, ///< 变倍步进值 [abl_ratio_e]（小数2位）
    MVS_DCTRL_ABLC_PT_SPEED,        ///< 转速范围   [abl_sensitivity_e]
    
    MVS_DCTRL_ABLC_NUM,
}mvs_dctrl_ablc_e;

/** 灯类能力集(data::light) */
typedef enum _dev_light_ability_code
{
    MVS_DLIGHT_ABLC_IRLED,          ///< 红外灯控制 [abl_light_ctrl_bmpc32_e]
    MVS_DLIGHT_ABLC_IRLED_SCHE,     ///< 红外灯定时 [abl_schedule_e]
    MVS_DLIGHT_ABLC_WLIGHT,         ///< 白光灯控制 [abl_light_ctrl_bmpc32_e]
    MVS_DLIGHT_ABLC_WLIGHT_SCHE,    ///< 白光灯定时 [abl_schedule_e]

    MVS_DLIGHT_ABLC_NUM,
}mvs_dlight_ablc_e;

/** 网络能力集(data::net) */
typedef enum _dev_net_ability_code
{
    MVS_DNET_ABLC_NETWORK_IF,       ///< 网络接口   [abl_network_if_bmpc32_e]
    MVS_DNET_ABLC_NETWORK_CFG,      ///< 网络配置   [abl_network_cfg_bmpc32_e]

    MVS_DNET_ABLC_NUM,
}mvs_dnet_ablc_e;

/** 报警能力集(data::alert) */
typedef enum _dev_alert_ability_code
{
    MVS_DALERT_ABLC_PROTOCOL,       ///< 报警协议     [1=GID10；2=GID14]
    MVS_DALERT_ABLC_COMMON_CFG,     ///< 通用功能     [abl_alert_cfg_bmpc32_e]
    MVS_DALERT_ABLC_DETECT_EVENT,   ///< 侦测能力     [abl_alert_detect_bmcp32_e]
    MVS_DALERT_ABLC_DETECT_OBJECT,  ///< 分类能力     [abl_alert_object_bmcp32_e]
    MVS_DALERT_ABLC_AREA_TYPE,      ///< 区域类型     [abl_zone_e]
    MVS_DALERT_ABLC_SOUND,          ///< 报警音能力   [abl_alert_sound_bmpc32_e]
    MVS_DALERT_ABLC_WARNING_LIGHT,  ///< 报警灯能力   [abl_alert_wl_bmpc32_e]
    MVS_DALERT_ABLC_EVT_ATTR,       ///< 事件属性能力 [abl_alert_evt_bmpc32_e]
    MVS_DALERT_ABLC_OBJ_ATTR,       ///< 对象属性能力 [abl_alert_obj_attr_bmpc32_e]

    MVS_DALERT_ABLC_NUM,
}mvs_dalert_ablc_e;

/** 杂项能力集(data::misc) */
typedef enum _dev_misc_ability_code
{
    MVS_DMISC_ABLC_BINDING,         ///< 支持绑定方式 [abl_binding_bmpc32_e]
    MVS_DMISC_ABLC_BINDING_PREFS,   ///< 首选绑定方式 [abl_binding_bmpc32_e]
    MVS_DMISC_ABLC_LENS,            ///< 镜头能力   [abl_lens_bmpc32_e]
    MVS_DMISC_ABLC_RECORD,          ///< 录像能力   [abl_record_bmpc32_e]
    MVS_DMISC_ABLC_SDCARD,          ///< 存储卡操作 [abl_sdcard_bmpc32_e]
    MVS_DMISC_ABLC_PROMPT,          ///< 提示音     [abl_prompt_bmpc32_e]
    MVS_DMISC_ABLC_MAINT,           ///< 设备维护   [abl_maintenance_bmpc32_e]
    MVS_DMISC_ABLC_EXTPROT,         ///< 扩展协议   [abl_extprotocol_bmpc32_e]
    MVS_DMISC_ABLC_RECORD_VQUALITY, ///< 录像质量   [abl_video_quality_bmpc32_e]

    MVS_DMISC_ABLC_NUM,
}mvs_dmisc_ablc_e;

#pragma mark -----能力结构类型-----
//视频流能力
typedef struct
{
    BOOL isCapture;         //视频采集
    BOOL isDisplay;         //视屏播放
    BOOL isEncodeChange;    //编码类型切换
    BOOL isThermalImage;    //热成像
}_video_ability;

//音频流能力
typedef struct
{
    BOOL isCapture;         //音频采集
    BOOL isPlay;            //音频播放（对讲）
    BOOL isCaptureVolume;   //采集音量调节
    BOOL isPlayVolume;      //播放音量调节（对讲）
    BOOL isEncodeChange;    //编码类型切换
}_audio_ability;

//视频流编解码能力
typedef struct
{
    BOOL isMJPEG;   //MJPEG
    BOOL isH264;    //H264
    BOOL isH265;    //H265
}_video_codec_ability;

//音频流编解码能力
typedef struct
{
    BOOL isPCM;         //PCM
    BOOL isADPCM;       //ADPCM
    BOOL isADTS_ACC;    //ADTS_ACC
    BOOL isG711A;       //G711A
    BOOL isG711U;       //G711U
}_audio_codec_ability;

//视频质量能力
typedef struct
{
    BOOL isSD;  //标清
    BOOL isHD;  //高清
    BOOL isFHD; //全高清
}_video_quality_ability;

//云台控制能力
typedef struct
{
    BOOL isHorizontal;  //水平电机
    BOOL isVertical;    //垂直电机
    BOOL isSpeed;       //转速设置
    BOOL isObjTrack;    //运动跟踪
    BOOL isRecal;       //手动校准
    BOOL isAutoRecal;   //自动校准
    int ptSpeed;        //云台转速范围
}_pt_ctrl_ability;

//镜头能力（两者都为NO则代表普通镜头）
typedef struct
{
    BOOL isWallPano;    //挂壁（180°）全景
    BOOL isCeilingPano; //吸顶（360°）全景
}_lens_ability;

//变焦变倍能力
typedef struct
{
    BOOL isSupport;     //变倍控制
    BOOL isRefocus;     //自动（校准）对焦
    BOOL isManualFocus; //手动调焦
}_zoom_ctrl_ability;

//图像旋转能力
typedef struct
{
    BOOL isFlipAndMirror;   //镜像翻转（非独立操作）
    BOOL isMirror;          //镜像
    BOOL isAngle;           //角度（固定角度）
}_cam_rotate_ability;

//灯能力
typedef struct
{
    BOOL isSwitch;      //手动开关（包含自动）
    BOOL isSchedule;    //定时设置
}_light_ctrl_ability;

//夜视能力
typedef struct
{
    BOOL isNormal;          //支持普通夜视（自动）
    BOOL isNormalManual;    //支持普通夜视（手动：开/关）
    BOOL isColor;           //支持全彩夜视（自动）
    BOOL isColorManual;     //支持全彩夜视（手动：开/关）
}_nightvision_ability;

//图像调节能力
typedef struct
{
    BOOL isAntiFlicker; //抗频闪
}_isp_cfg_ability;

//OSD能力
typedef struct
{
    BOOL isDate;        //日期OSD（开关）
    BOOL isText;        //文本OSD（开关、修改）
    BOOL isLogo;        //图片OSD（开关、修改）
    BOOL isPosition;    //OSD位置修改
}_osd_cfg_ability;

//网络接口
typedef struct
{
    BOOL isWIFI_2_4_G;  //wifi-2.4g
    BOOL isWIFI_5_8_G;  //wifi-5.8g
    BOOL isEthernet;    //以太网
    BOOL isLTE;         //移动网络
    BOOL isBLE;         //蓝牙
}_network_if_ability;

//绑定方式
typedef struct
{
    BOOL isQRCode;  //二维码绑定
    BOOL isPincode; //pincode绑定
    BOOL isWPS;     //物理验证绑定
}_binding_ability;

//网络配置能力
typedef struct
{
    BOOL isRouterCFG;   //路由配置（wifi/...）
    BOOL isStaticIP;    //静态IP（wifi/ethemet/...）
}_network_cfg_ability;

//报警配置能力
typedef struct
{
    BOOL isArming;          //布撤防
    BOOL isSchedule;        //报警d
    BOOL isManuallyAlert;   //手动报警
    BOOL isCoustomArmAudio; //自定义报警音
    BOOL isArmAudioMusicList; //报警音音乐列表关联
    BOOL isAlertLight;       //报警灯
}_alert_cfg_ability;

//报警侦测能力
typedef struct
{
    BOOL isMotion;          //运动侦测
    BOOL isPersonStay;      //人员逗留侦测
    BOOL isEfence; //电子围栏
    BOOL isLineCrossing; //越线侦测
    BOOL isBabyCry; //哭声检测
}_detect_ability;

//分类能力
typedef struct
{
    BOOL isAnyMous;  // 其他未细分对象
    BOOL isPerson;   //人形
    BOOL isSmoke;    //烟雾

}_alert_object_ability;

//录像能力
typedef struct
{
    BOOL isSpontaneous;     //连续录像
    BOOL isEvent;           //事件录像
    BOOL isTLV;             //浓缩录像
    ///< ...预留
    BOOL isCFGWithAudio;    //录像音频
}_record_ability;

//存储卡能力
typedef struct
{
    BOOL isCapacity;        //存储卡容量
    BOOL isFormat;          //格式化
    BOOL isManuallyCtrl;    //手动操作（挂载/弹出）
}_sdcard_ability;

//提示音能力
typedef struct
{
    BOOL isNormal;          //普通提示音（含开关）
    BOOL isAlert;           //报警提示音（含开关）
    BOOL isCustomise;       //自定义提示音
    BOOL isCustomiseAlert;  //自定义报警提示音
    BOOL isLanguage;        //语言切换
}_prompt_ability;

//扩展协议能力
typedef struct
{
    BOOL isONVIF;   //ONVIF协议
}_extprotocol_ability;

//设备维护能力
typedef struct
{
    BOOL isReboot;      //远程重启
    BOOL isAutoReboot;  //自动重启
}_maintenance_ability;

//流能力集
typedef struct
{
    _video_ability videoAbility;                //视频流
    _video_codec_ability videoEncoderAbility;   //视频流编码
    _video_codec_ability videoDecoderAbility;   //视频流解码
    _audio_ability audioAbility;                //音频流
    _audio_codec_ability audioEncoderAbility;   //音频流编码
    _audio_codec_ability audioDecoderAbility;   //音频流解码
    _video_quality_ability videoQualityAbility; //视频质量支持
    int videoDecodeMaxWidthPixel;               //视频解码最大宽度 pixel
    int videoDecodeMaxHeightPixel;              //视频解码最大高度 pixel
    int maxFps;                                 //视频最大帧率 
}_stream_ability;

//图像能力集
typedef struct
{
    _cam_rotate_ability camRotateAbility;       //图像旋转
    _isp_cfg_ability ispAbility;                //图像设置
    _nightvision_ability nightVisionAbility;    //夜视能力
    _osd_cfg_ability osdAbility;                //水印能力
}_image_ability;

//控制能力集
typedef struct
{
    _pt_ctrl_ability ptCtrlAbility;     //云台控制
    unsigned int ptPresetsAbility;      //预置位 [abl_slot_e]
    unsigned int ptAutoCruiseAbility;   //自动巡航 [abl_schedule_e]
    unsigned int ptCruiseSche;          //定时巡航 [abl_schedule_e]
    _zoom_ctrl_ability zoomAbility;     //变倍变焦
    double zoomRatioMax;                //最大变倍率 [abl_ratio_e]
    double zoomRatioStep;               //变倍步进值 [abl_ratio_e]
    unsigned int ptSpeed;          //云台转速范围 [abl_sensitivity_e]
}_ctrl_ability;

//灯类能力集
typedef struct
{
    _light_ctrl_ability irLedAbility;   //红外灯控制
    unsigned int irLedScheAbility;      //红外灯定时 [abl_schedule_e]
    _light_ctrl_ability wLightAbility;  //白光灯控制
    unsigned int wLightScheAbility;     //白光灯定时 [abl_schedule_e]
}_light_ability;

//网络能力集
typedef struct
{
    _network_if_ability networkIfAbility;   //网络接口
    _network_cfg_ability networkCfgAbility; //网络配置
}_net_ability;


/** 报警音能力 */
typedef struct
{
    BOOL isSoundBasic;  //支持提示音（开关）
    BOOL isSoundCustom; //自定义提示音
    BOOL isSoundMusicList; //音乐列表关联
    
}_alert_sound;
/** 报警事件属性能力 */
typedef struct
{
    BOOL isEVTSensitivity;  //灵敏度
    BOOL isEVTWarnLight;  //警示灯
    BOOL isEVTSound;  //报警音
}_alert_evt;
/** 报警对象能力 */
typedef struct
{
    BOOL isSensitivity;  //置信度
    BOOL isThreshold;    //触发阈值（感知类或数值类对象）/检测大小限制（识别类对象）
    BOOL isWarnLight;    //警示灯
    BOOL isSound;        //报警音
    BOOL isTagDraw;      //标签绘制（画框/标签）
    BOOL isPerceptionOnly;  //仅支持感知（无法结合图像定位）
}_alert_obj_attr;
//报警能力集
typedef struct
{
    unsigned int alertProtocal ; //协议版本
    _alert_cfg_ability alertCfgAbility ;//通用功能
    _detect_ability detectAbility ;//侦测能力
    _alert_object_ability objectAbility; //分类能力
    abl_zone_e zoneType; //区域类型
    _alert_sound soundAbility; //报警音能力
    unsigned int alertWL; //报警灯能力
    _alert_evt evtAbility ; //事件属性能力
    _alert_obj_attr objAttrAbility; //对象属性能力
    
}_alert_ability;
//杂项能力值
typedef struct
{
    int bindingAbility;                             //支持绑定方式
    int bindingPrefsAbility;                        //首选绑定方式
    _lens_ability lensAbility;                      //镜头能力
    _record_ability recordAbility;                  //录像能力
    _sdcard_ability sdCardAbility;                  //存储卡操作
    _prompt_ability promptAbility;                  //提示音
    _maintenance_ability maintAbility;              //设备维护
    _extprotocol_ability extprotAbility;            //扩展协议
    _video_quality_ability recordVQualityAbility;   //录像质量
}_misc_ability;

#endif /* DeviceAbilityDefinition_h */
