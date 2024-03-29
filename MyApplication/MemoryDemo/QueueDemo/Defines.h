//
//  Defines.h
//  iCamSee
//
//  Created by macrovideo on 15/10/19.
//  Copyright © 2015年 macrovideo. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef Defines_h
#define Defines_h

//MARK: 设备登陆使用
enum{
    VERIFY_DEVICE_ID_ERR=-2,	//设备ID错误
    VERIFY_FAILED=-1,	        //校验失败
    NOT_SUPPORT_CMD=-10,        //设备不支持（新设备必须走新登录协议）20200521
    USER_NOT_EXIST=0,	        //用户不存在
    PWD_ERROR=1,		        //密码错误
    NO_PRI=2,			        //权限不足
    AUDIO_PRI=4,			    //权限不足
    CTRL_PRI=8,			        //云台控制
    PLAYBACK_PRI=16,	        //录像回放
    RECEIVE_PRI=32,		        //远程接收
    SPEAK_PRI=64                //远程对讲
};

//MARK: 音视频帧类型
typedef enum
{
    FRAMETYPE_I 		    = 0,		//I÷°
    FRAMETYPE_P 		    = 1,		//P÷°
    SUBFRAMETYPE_I 		    = 2,		//SubStream I÷° ◊¢“‚ Frametype ∂®“Â”Î NV7000SDK.dll÷–µƒ∂®“Â≤ªÕ¨
    SUBFRAMETYPE_P 		    = 3,		//SubStream P÷°
    FRAMETYPE_MP2		    = 4,		//MPEG-1 Layer2“Ù∆µ÷°
    FRAMETYPE_ULAWPCM 	    = 5,		//u-LAW PCM“Ù∆µ÷°
    FRAMETYPE_B			    = 6,
    SUBFRAMETYPE_B		    = 7,
    FRAMETYPE_MD		    = 8,		//“∆∂Ø’Ï≤‚÷°
    FRAMETYPE_JPEG          = 9,        //¿©’π÷ß≥÷MotionJPEG FrameType
    FRAMETYPE_THERMAL       = 10,        //¿©’π÷ß≥÷MotionJPEG FrameType
    FRAMETYPE_SYSHEADER     = 16,		//œµÕ≥–≈œ¢÷°
    FRAMETYPE_PCM           = 21,		//œµÕ≥–≈œ¢÷°
    FRAMETYPE_ADPCM         = 22,		//œµÕ≥–≈œ¢÷°
    FRAMETYPE_MP3           = 23,		//œµÕ≥–≈œ¢÷°
    FRAMETYPE_AAC           = 24,		//œµÕ≥–≈œ¢÷°
    FRAMETYPE_G711          = 26,
    FRAMETYPE_MPEG4_I       = 36,		//œµÕ≥–≈œ¢÷°
    FRAMETYPE_MPEG4_P       = 37,		//œµÕ≥–≈œ¢÷°
    FRAMETYPE_H265_I        = 40,		//œµÕ≥–≈œ¢÷°
    FRAMETYPE_H265_P        = 41,		//œµÕ≥–≈œ¢÷°
    FRAMETYPE_H264_TIME_I   = 50,		//œµÕ≥–≈œ¢÷°
    FRAMETYPE_H264_TIME_P   = 51,		//œµÕ≥–≈œ¢÷°
    FRAMETYPE_H265_TIME_I   = 52,		//œµÕ≥–≈œ¢÷°
    FRAMETYPE_H265_TIME_P   = 53,
    FRAMETYPE_WIFI_SIGNAL   = 91,       //add by yang 20190627 WiFi信号强度
    FRAMETYPE_BATTERY       = 92,        //add by weibin 20190910 设备电量信息
    FRAMETYPE_PTZXCRUISE    = 93,
    FRAMETYPE_LENS_STATUS   = 94,       //add by qin 20201210 镜头控制信息
    FRAMETYPE_PRIVATE_MODE  = 95,       //20210930 隐私模式信息
    FRAMETYPE_TALK_MODE     = 96,       //20240220 双向对讲模式
    FRAMETYPE_YUV420P          = 1000,        //¿©’π÷ß≥÷MotionJPEG FrameType (仅用于本地录像MP4生成)
} PACKET_TYPE;


enum//
{
    DOWNREQUEST         =   100,
    STOPDOWN            =   101,
    UPLOADQUEST         =   102,
    STOPUPLOAD          =   103,
    FILESTART           =   110,
    FILEDATAEND         =   111,
    FILEDATA            =   112,
    FILEERROR           =   113,
    USERVERIFY          =   167,
    USERVERIFYRESULT    =   168,
    USERVERIFYRESULTMR  =   169,
    TESTCONNECTION      =   222,
    DISCONNECT          =   253,
    CUSTOMBUF           =   254
};



//声网
#define kAgoraAppID @"a8eba2442a5749ca9ce116901e24b407"

//新平台
#define ACTIVATION_LAN_REQ  0x38110818   //本地账号激活请求
#define ACTIVATION_LAN_RESP 0x38110828   //本地账号激活返回

#endif /* Defines_h */

#define VALUE_DISBLE 0
#define VALUE_ENABLE 1

#define CMD_MR_PLAY 1002
#define CMD_MR_PLAY_RESPONSE 2002
#define CMD_MR_GET_IMAGE 1003

#define CMD_MR_OK 100
#define CMD_MR_FAIL 101

#define TIMESTAMP_TYPE_UNKNOW   0
#define TIMESTAMP_TYPE_NONE     1
#define TIMESTAMP_TYPE_SEC      2
#define TIMESTAMP_TYPE_USEC     3

//add by luo 20151204
#define ZONE_AUTO 0  //自动
#define ZONE_CHINA 1 //中国大陆
#define ZONE_AS1 2   //亚洲1区
#define ZONE_AS2 3  //亚洲2区
#define ZONE_AS3 4  //亚洲3区
#define ZONE_AS4 5  //亚洲4区
#define ZONE_NA1 6  //北美
#define ZONE_SA1 7  //南美
#define ZONE_EU1 8  //欧洲1区
#define ZONE_EU2 9  //欧洲2区
#define ZONE_OA1 10 //大洋洲
#define ZONE_AF1 11 //非洲1区
#define ZONE_AF2 12 //非洲2区

#ifndef _COMMON
#define _COMMON
struct _tagDomainIPMAP {
 bool isInitRS1;
 char pIPRS1[20];
 bool isInitRS2;
 char pIPRS2[20];
 bool isInitRS3;
 char pIPRS3[20];
 
 //
 bool isInitENRS1;
 char pIPENRS1[20];
 bool isInitENRS2;
 char pIPENRS2[20];
 bool isInitENRS3;
 char pIPENRS3[20];
 
 //
 bool isInitAS1;
 char pIPAS1[20];
 bool isInitAS2;
 char pIPAS2[20];
 bool isInitAS3;
 char pIPAS3[20];
 bool isInitAS4;
 char pIPAS4[20];
 
 bool isInitNA1;
 char pIPNA1[20];
 bool isInitSA1;
 char pIPSA1[20];
 
 bool isInitEU1;
 char pIPEU1[20];
 bool isInitEU2;
 char pIPEU2[20];
 
 bool isInitOA1;
 char pIPOA1[20];
 
 bool isInitAF1;
 char pIPAF1[20];
 bool isInitAF2;
 char pIPAF2[20];
 
 };
#endif
typedef struct _tagDomainIPMAP DOMAIN_IP_MAP, *PDOMAIN_IP_MAP;
//全景URL
#define MR_SERVER_AS105 "vri1.av380.net"//add by lusongbin
#define MR_SERVER_AS30 "vri2.av380.net"//add by lusongbin
#define MR_SERVER_AS34 "vri3.av380.net"//add by lusongbin

//全景IP
#define MR_SERVER_IP105 "47.104.4.169"
#define MR_SERVER_IP30 "47.104.4.130"
#define MR_SERVER_IP34 "47.97.166.47"


#define MR_SERVER_RS1 "is581.nvcam.net"
#define MR_SERVER_RS2 "is582.nvcam.net"
#define MR_SERVER_RS3 "is583.nvcam.net"

//
#define MR_SERVER_IP1 "47.97.166.47"//modify 20161122 as30
#define MR_SERVER_IP2 "120.78.86.169"//modify 20161122 as34
#define MR_SERVER_IP3 "118.190.204.96"


#define EN_MR_SERVER_RS1 "hk1.nvcam.net"
#define EN_MR_SERVER_RS2 "hk2.nvcam.net"
#define EN_MR_SERVER_RS3 "hk3.nvcam.net"

#define EN_MR_SERVER_IP1 "47.244.109.43"
#define EN_MR_SERVER_IP2 "47.254.33.16"
#define EN_MR_SERVER_IP3 "47.75.91.236"

#define MR_SERVER_AS1 "zoneas1.nvcam.net"//亚洲1 (日本，韩国，台湾，香港，泰国，越南)
#define MR_SERVER_AS2 "zoneas2.nvcam.net"//亚洲2 (马来西亚,新加坡)
#define MR_SERVER_AS3 "zoneas3.nvcam.net"//亚洲3 (西亚)
#define MR_SERVER_AS4 "zoneas4.nvcam.net"//亚洲4 (日本，韩国，台湾，香港，泰国，越南)

#define MR_SERVER_NA1 "zonena1.nvcam.net"//北美
#define MR_SERVER_SA1 "zonesa1.nvcam.net"//南美

#define MR_SERVER_EU1 "zoneeu1.nvcam.net"//欧洲1
#define MR_SERVER_EU2 "zoneeu2.nvcam.net"//欧洲2

#define MR_SERVER_OA1 "zoneOa1.nvcam.net"//澳大利亚,新西兰

#define MR_SERVER_AF1 "zoneaf1.nvcam.net"//非洲1
#define MR_SERVER_AF2 "zoneaf2.nvcam.net"//非洲2

#define EN_MR_SERVER_IPSGP "47.244.109.43"
#define EN_MR_SERVER_IPHK "47.88.29.73" // modify by GWX 20200306,旧IP过期，更新新IP([旧]47.254.20.205-->[新]47.88.29.73)
#define EN_MR_SERVER_IPAM "47.75.91.236"

//#define MR_SERVER_RS1 "115.28.54.85"
//#define MR_SERVER_RS2 "115.28.54.85"
//#define MR_SERVER_RS3 "115.28.54.85"
//
//#define MR_SERVER_IP1 "115.28.54.85"
//#define MR_SERVER_IP2 "115.28.54.85"
//#define MR_SERVER_IP3 "115.28.54.85"

//#define EN_MR_SERVER_RS1 "hk1.nvcam.net"
//#define EN_MR_SERVER_RS2 "hk2.nvcam.net"
//#define EN_MR_SERVER_RS3 "hk3.nvcam.net"
//
//#define EN_MR_SERVER_IP1 "203.88.173.221"
//#define EN_MR_SERVER_IP2 "47.88.0.218"
//#define EN_MR_SERVER_IP3 "203.88.173.221"


//add by luo 20170619
#define CMD_PLAY_REQUEST 301
#define CMD_PLAY_RESPONSE 401
#define CMD_PLAY_VERIFY 302
#define CMD_PLAY_VERIFY_RESPONSE 402
#define CMD_PLAY_GET_MEDIA_DATA 303
#define CMD_PLAY_GET_MEDIA_DATA_LONGSIZE 333
#define CMD_CTRL_SHUTDOWN 1008

//end add by luo 20170619

//add by luo 20170622
//MARK: 预览使用
#define VERIFY_RESULT_OK                        1001 //验证成功
#define VERIFY_RESULT_FAIL                      1002 //验证失败

#define VERIFY_DES_OLD_VERSION                  -11 //旧版本
#define VERIFY_DES_ERROR                        -1  //描述错误
#define VERIFY_DES_UDPMAKEHOLESUCCEED_NOREPLY   -2  //UDP打洞成功, 但没有响应
#define VERIFY_DES_SOCK5CONNECTSUCCEED_NOREPLY  -3  //SOCK连接成功, 但没有响应
#define VERIFY_DES_TCPCONNECTSUCCEED_NOREPLY    -4  //TCP连接成功, 但没有响应
#define VERIFY_DES_SOCK5CONNECTFAIL             -5  //SOCKET连接失败
#define VERIFY_DES_TCPCONNECTFAIL               -6  //TCP连接失败
#define VERIFY_DES_MAKEHOLEFIAL                 -7  //打洞失败
#define VERIFY_DES_MAKEHOLE_VNNSERVERNOCONNECT  -8  //
#define VERIFY_DES_MAKEHOLE_TIMEOUT             -9  //打洞超时
#define VERIFY_DES_MAKEHOLE_INTERNOCONNECT      -10 //
#define VERIFY_DES_HANDLE_EXPIRTED              -11 //handle过期
#define VERIFY_DES_HANDLE_ERR                   -12 //handle错误
//end add by luo 20170622

#define OPERATION_RESULT_SUCCEED            1000 //操作成功
#define OPERATION_RESULT_SUCCEED_LAN_V20    1001 //操作成功(新协议, 局域网)
#define OPERATION_RESULT_OLDVERION          1001 //not used
#define OPERATION_RESULT_FAILED             -1001//操作失败


//add by luo 20170626
#define NV_VERSION_V20 20//
#define MEDIA_BUF_SIZE_32 32   //媒体数据包包大小

#define NV_IPC_WIFI_SEARCH_REQUEST_V20 310 //
#define NV_IPC_WIFI_SEARCH_RESPONSE_V20 410 //±æµÿwifiÀ—À˜œÏ”¶÷∏¡Ó◊÷
#define NV_IPC_WIFI_SEARCH_RESPONSE_WAIT_V20 510 //±æµÿwifiÀ—À˜œÏ”¶÷∏¡Ó◊÷

#define NV_IPC_WIFI_GET_CONFIG_REQUEST_V20 311//
#define NV_IPC_WIFI_GET_CONFIG_RESPONSE_V20 411//

#define NV_IPC_WIFI_SET_CONFIG_REQUEST_V20 312//
#define NV_IPC_WIFI_SET_CONFIG_RESPONSE_V20 412//

#define NV_IPC_RECORD_CONFIG_GET_REQUEST_V20 313//
#define NV_IPC_RECORD_CONFIG_GET_RESPONSE_V20 413//

#define NV_IPC_RECORD_CONFIG_SET_REQUEST_V20 314//
#define NV_IPC_RECORD_CONFIG_SET_RESPONSE_V20 414//

#define NV_IPC_TIME_GET_REQUEST_V20 315//
#define NV_IPC_TIME_GET_RESPONSE_V20 415//

#define NV_IPC_TIME_SET_REQUEST_V20 316//
#define NV_IPC_TIME_SET_RESPONSE_V20 416//


#define NV_IPC_USERINFO_GET_REQUEST_V20 317//
#define NV_IPC_USERINFO_GET_RESPONSE_V20 417//

#define NV_IPC_USERINFO_SET_REQUEST_V20 318//
#define NV_IPC_USERINFO_SET_RESPONSE_V20 418//

#define NV_IPC_VERSION_INFO_GET_REQUEST_V20 319//
#define NV_IPC_VERSION_INFO_GET_RESPONSE_V20 419//

#define NV_IPC_WIFI_SELECT_SET_REQUEST_V20 320
#define NV_IPC_WIFI_SELECT_SET_RESPONSE_V20 420


#define NV_IP_SWITCH_GET_REQUEST_V20 321//获取开关指令字
#define NV_IP_SWITCH_GET_RESPONSE_V20 421 //获取开关响应指令字

#define NV_IP_SWITCH_SET_REQUEST_V20 322//设置开关指令字
#define NV_IP_SWITCH_SET_RESPONSE_V20 422 //设置开关响应指令字

#define NV_IPC_USERINFO_GET_RESPONSE_NEW 317//

#define NV_IP_ADD_USER_REQUEST_V20 323
#define NV_IP_ADD_USER_RESPONSE_V20 423

#define NV_IP_DELETE_USER_REQUEST_V20 324
#define NV_IP_DELETE_USER_RESPONSE_V20 424

#define NV_IP_MODIFY_USER_REQUEST_V20 325
#define NV_IP_MODIFY_USER_RESPONSE_V20 425

#define NV_IP_MODIFY_PWD_REQUEST_V20 326
#define NV_IP_MODIFY_PWD_RESPONSE_V20 426

#define NV_IP_UPDATE_CHECK_REQUEST_V20 327
#define NV_IP_UPDATE_CHECK_RESPONSE_V20 427

#define NV_IP_UPDATE_START_REQUEST_V20 328
#define NV_IP_UPDATE_START_RESPONSE_V20 428

#define NV_IP_PTZX_REQUEST_V20 329
#define NV_IP_PTZX_RESPONSE_V20 429

#define NV_IP_ALARM_DEVICE_LIST_REQUEST_V20 330
#define NV_IP_ALARM_DEVICE_LIST_RESPONSE_V20 430

#define NV_IP_ALARM_DEVICE_SEARCH_REQUEST_V20 331
#define NV_IP_ALARM_DEVICE_SEARCH_RESPONSE_V20 431

#define NV_IP_ALARM_DEVICE_ADD_REQUEST_V20 332
#define NV_IP_ALARM_DEVICE_ADD_RESPONSE_V20 432

#define NV_IP_ALARM_DEVICE_MODIFY_REQUEST_V20 333
#define NV_IP_ALARM_DEVICE_MODIFY_RESPONSE_V20 433

#define NV_IP_ALARM_DEVICE_DELETE_REQUEST_V20 334
#define NV_IP_ALARM_DEVICE_DELETE_RESPONSE_V20 434

#define NV_IP_WAIITING_RESPONSE_V20 435


#define NV_IP_FORMAT_SDCARD_REQUEST_V20 341
#define NV_IP_FORMAT_SDCARD_RESPONSE_V20 441

#define NV_IPC_IP_CONFIG_GET_REQUEST_V20 342
#define NV_IPC_IP_CONFIG_GET_RESPONSE_V20 442

#define NV_IPC_IP_CONFIG_SET_REQUEST_V20 343
#define NV_IPC_IP_CONFIG_SET_RESPONSE_V20 443

#define NV_IPC_ALARM_SET_REQUEST_V20 344
#define NV_IPC_ALARM_SET_RESPONSE_V20 444

#define NV_IPC_NEW_ALARM_SET_REQUEST 391  //新报警设置请求指令（AI人型检测报警）
#define NV_IPC_NEW_ALARM_SET_RESPONSE 491 //新报警设置响应指令
//end add by luo 20170626

#define NUMPERFRM                   505         //PCM音频解码器采样率

#define CNN_STAT_CONNENTING         0x1001      //连接中, NVPanoPlayer: 获取图像数据
#define CNN_STAT_LOADING            0x1002      //not used, NVPanoPlayer 预览
#define CNN_STAT_STOP               0x1003      //not used, NVPanoPlayer 预览

#define CNN_STAT_CONNECT_FAILED     0x1004      //远程配置
#define CNN_STAT_RECV_BAD           0x1005      //not used

#define CNN_STAT_RESTART            0x1006      //连接断开需要重启, NVPanoPlayer重现获取数据

#define MAX_FRAME_SIZE              9437184/2   //图像帧最大字节数, 4.5M
#define NEW_VERSION                 2           //设备版本
#define EACH_GETFRAME_COUNT         100         //每次获取的帧数

#define EACH_GETFRAME_COUNT_L5      500         //每次获取的帧数


#define CMD_READY                   0x1001      //局域网 1.0 协议: 设备与手机端准备好发送图像数据
#define CMD_GET_IMAGE               0x2001      //局域网 1.0 协议: 向设备端请求发送图像数据
#define PARAM_NONE                  0x3000      //成功收到图像帧数据
#define PARAM_IFRAME                0x3001      //I帧数据
#define PARAM_PFRAME                0x3002      //P帧数据

#define REC_FILE_PLAYBACK_GET_DATA  158         //请求录像回放文件数据, 下一步进入获取数据循环
#define REC_FILE_PLAYBACK_FINISH    159         //向服务器发送停止: 录像回放


#define MEDIA_PACKET_HEADER_SIZE    8           //媒体数据包的包头大小
#define MEDIA_PACKET_SIZE           412         //媒体数据包的包大小
#define MEDIA_BLOCK_SIZE            404         //媒体数据包的负载大小
#define PACKET_HEADER_FLAG          0x7F        //媒体数据包包头标识

#define FRAME_BUF_MAX_SIZE          704*576*3   //帧数据接收Buffer的最大值


#define PACKET_BUF_LENGTH           520         //一般数据包大小, 512+4+4
#define PACKET_BUF_SEND_LENGTH      256         //512+4+4

#define MEDIA_PACKET_HEADER_SIZE_V3 12          //媒体数据包的包头大小, 新版
#define MEDIA_PACKET_SIZE_V3        512         //媒体数据包的包大小, 新版
#define MEDIA_BLOCK_SIZE_V3         500         //媒体数据包的负载大小, 新版

#define LONG_PACKET_MODE            30          //长包模式
#define SHORT_PACKET_MODE           20          //短包模式

//MARK: 数据包缓冲区大小
#define MEDIA_BUF_SIZE              412         //媒体数据包的buffer大小(局域网收发数据缓冲区)
#define MEDIA_BUF_SIZE_FILE_SEARCH  512         //文件搜索的buffer大小(收发数据缓冲区)
#define MEDIA_BUF_SIZE_MR           256         //媒体数据包的包大小(互联网收发缓冲区)
#define MEDIA_BUF_SIZE_SEARCH       102400         //100k 媒体数据包的buffer大小(局域网收发数据缓冲区)

#define MEDIA_PACKET_LONGSIZE_V20   8012        //4G网络 大于1.0的新协议, 设备端发送图像帧的分包大小
#define MEDIA_BLOCK_LONGSIZE_V20    8000        //4G网络 大于1.0的新协议, 设备端发送图像帧的分包大小中的有效载荷
#define MEDIA_PACKET_MAX_SIZE_EX    8013        //4G网络 大于1.0的新协议, 申请图像帧的分包的堆内存大小

#define SERVER_TYPE_DOMAIN          1001        //地址类型, 域名 not used
#define SERVER_TYPE_IP              1002        //地址类型, IP


#define PLAY_RESULT_OK              100         //从云端下载回放录像完毕
#define PLAY_RESULT_CONN_FAIL       -101        //socket连接失败, 默认值
#define PLAY_RESULT_PLAY_FAIL       -103        //
#define PLAY_RESULT_PARAM_INVALID   -104

#define LOGIN_RESULT_SUCCESS        1001        //登录成功
#define LOGIN_RESULT_UNSUPPORT      -100        //登录失败: 固件太老, 不支持

//MARK: 云台(PTZ)控制
#define NV_IPC_PTZ_REQUEST                  170     //云台(PTZ)控制指令
#define NV_IPC_PRESET_REQUEST               171     //云台(PTZ)预置位控制指令
#define NV_IPC_PTZ_ACTION_NONE              1000    //云台: 没有动作
#define NV_IPC_PTZ_ACTION_LEFT              1001    //云台: 左转
#define NV_IPC_PTZ_ACTION_RIGHT             1002    //云台: 右转
#define NV_IPC_PTZ_ACTION_UP                1003    //云台: 向上
#define NV_IPC_PTZ_ACTION_DOWN              1004    //云台: 向下
#define NV_IPC_PTZ_ACTION_AUTO_HORIZONTAL   1005    //云台: 自动水平
#define NV_IPC_PTZ_ACTION_AUTO_VERTICAL     1006    //云台: 自动垂直
#define NV_IPC_PTZ_ACTION_AUTO_ALL          1007    //云台: 自动

//MARK: 声音控制
#define CMD_SOUND_CTRL              0x2101      //声音开关控制
#define SOUND_CTRL_CLOSE            0x1000      //停止接收声音
#define SOUND_CTRL_OPEN             0x1001      //开启接收声音

//MARK: 对讲模式控制 （半双工、全双工）
#define CMD_TALK_MODE_CTRL          191

//MARK: 视频格式
#define NV_CODEC_ID_H264            1001        //h.264编码
#define NV_CODEC_ID_MPEG4           1002        //mpeg4编码
#define NV_CODEC_ID_MJPEG           1003        //mjpeg编码
#define NV_CODEC_ID_H265            1004        //h.265编码

//MARK: WiFi列表
#define NV_IPC_WIFI_SEARCH_REQUEST          110     //WiFi列表获取CMD(发请求)
#define NV_IPC_WIFI_SEARCH_RESPONSE         210     //WiFi列表获取 响应CMD(收)
#define NV_IPC_WIFI_SEARCH_RESPONSE_WAIT    310     //WiFi列表获取等待CMD(收)

//MARK: 网络设置
#define NV_IPC_WIFI_GET_CONFIG_REQUEST      111     //网络配置获取CMD(发请求)
#define NV_IPC_WIFI_GET_CONFIG_RESPONSE     211     //网络配置获取 响应CMD(收)
#define NV_IPC_WIFI_SELECT_SET_REQUEST      120     //设置网络配置CMD(发请求)
#define NV_IPC_WIFI_SELECT_SET_RESPONSE     220     //设置网络配置 响应CMD(收)

//MARK: 录像设置
#define NV_IPC_RECORD_CONFIG_GET_REQUEST    113     //录像配置获取CMD(发请求)
#define NV_IPC_RECORD_CONFIG_GET_RESPONSE   213     //录像配置获取 响应CMD(收)
#define NV_IPC_RECORD_CONFIG_SET_REQUEST    114     //设置录像配置CMD(发请求)
#define NV_IPC_RECORD_CONFIG_SET_RESPONSE   214     //设置录像配置 响应CMD(收)

//MARK: 时间设置
#define NV_IPC_TIME_GET_REQUEST             115     //时间配置获取CMD(发请求)
#define NV_IPC_TIME_GET_RESPONSE            215     //时间配置获取 响应CMD(收)
#define NV_IPC_TIME_SET_REQUEST             116     //设置时间配置CMD(发请求)
#define NV_IPC_TIME_SET_RESPONSE            216     //设置时间配置 响应CMD(收)

//MARK: 用户信息(针对某个设备)
#define NV_IPC_USERINFO_GET_REQUEST         117     //用户信息获取CMD(发请求)
#define NV_IPC_USERINFO_GET_RESPONSE        217     //用户信息获取 响应CMD(收)
#define NV_IPC_USERINFO_SET_REQUEST         118     //设置用户信息CMD(发请求)
#define NV_IPC_USERINFO_SET_RESPONSE        218     //设置用户信息 响应CMD(收)

//MARK: 设备版本信息(固件,内核,更新等)
#define NV_IPC_VERSION_INFO_GET_REQUEST     119     //版本信息获取CMD(发请求)
#define NV_IPC_VERSION_INFO_GET_RESPONSE    219     //版本信息获取 响应CMD(收)

//MARK: 所有远程配置信息
#define CMD_GET_DEVICE_CONFIG_REQ           365     //设备所有配置信息获取CMD(发请求)
#define CMD_GET_DEVICE_CONFIG_RESP          465     //设备所有配置信息获取 响应CMD(收)

//MARK: 报警设置
#define NV_IP_SWITCH_GET_REQUEST            121     //报警配置获取CMD(发请求)
#define NV_IP_SWITCH_GET_RESPONSE           221     //报警配置获取 响应CMD(收)
#define NV_IP_SWITCH_SET_REQUEST            122     //设置报警配置CMD(发请求)
#define NV_IP_SWITCH_SET_RESPONSE           222     //设置报警设置 响应CMD(收)

//MARK: 设备可更新版本信息(当前版本,新版本)
#define NV_IP_UPDATE_CHECK_REQUEST          127     //可更新版本信息获取CMD(发请求)
#define NV_IP_UPDATE_CHECK_RESPONSE         227     //可更新版本信息获取 响应CMD(收)

//MARK: 设备更新
#define NV_IP_UPDATE_START_REQUEST          128     //更新设备CMD(发请求)
#define NV_IP_UPDATE_START_RESPONSE         228     //更新设备 响应CMD(收)

//MARK: 预置位设置
#define NV_IP_PTZX_REQUEST                  129     //设置预置位CMD(发请求)
#define NV_IP_PTZX_RESPONSE                 229     //设置预置位 响应CMD(收)
#define NV_IP_PTZX_REQUEST_EX               329     //设置预置位CMD(发请求 V20)
#define NV_IP_PTZX_RESPONSE_EX              429     //设置预置位 响应CMD(收 V20)

//MARK: SD格式化
#define NV_IP_FORMAT_SDCARD_REQUEST         141     //SD卡格式化CMD(发请求)
#define NV_IP_FORMAT_SDCARD_RESPONSE        241     //SD卡格式化 响应CMD(收)

//MARK: IP信息(DNS, netmask, DHCP等)
#define NV_IPC_IP_CONFIG_GET_REQUEST        142     //IP信息获取CMD(发请求)
#define NV_IPC_IP_CONFIG_GET_RESPONSE       242     //IP信息获取 响应CMD(收)
#define NV_IPC_IP_CONFIG_SET_REQUEST        143     //IP信息设置CMD(发请求)
#define NV_IPC_IP_CONFIG_SET_RESPONSE       243     //IP信息设置 响应CMD(收)

//MARK: 布撤防
#define NV_IPC_ALARM_SET_REQUEST            144     //布撤防CMD(发请求)
#define NV_IPC_ALARM_SET_RESPONSE           244     //布撤防 响应CMD(收)
#define NV_IPC_ALARM_SET_REQUEST_20         344     //布撤防CMD(发请求 V20)
#define NV_IPC_ALARM_SET_RESPONSE_20        444     //布撤防 响应CMD(收 V20)

//MARK: 热成像
#define NV_IPC_THERMAL_INFO_REQUEST         373     //热成像CMD(发请求)
#define NV_IPC_THERMAL_RESPONSE             473     //热成像 响应CMD(收)

//MARK: 预置位巡航
#define NV_IPC_PTZXCRUISE_INFO_REQUEST         374     //预置位巡航CMD(发请求)
#define NV_IPC_PTZXCRUISE_RESPONSE             474     //预置位巡航 响应CMD(收)

//MARK: 录像文件相关CMD
#define REC_FILE_PLAYBACK                   152     //录像回放CMD(发送请求)
#define REC_FILE_PLAYBACK_RESP              252     //录像回放 响应CMD(收)

//MARK: 登录指令CMD (deprecate)
#define CMD_LOGIN_EX                        154     //登录请求CMD(发送请求 deprecate)
#define CMD_LOGIN_EX_RESP                   254     //登录请求 响应CMD(收 deprecate)

//MARK: 录像回放CMD V20
#define REC_SEG_SEARCH_REQ                  361     //录像搜索CMD(发请求)
#define REC_SEG_SEARCH_RESP                 461     //录像搜索 响应CMD(收)
#define REC_SEG_SEARCH_RECV_REQ             362     //录像搜索接收数据CMD(发请求)
#define REC_SEG_SEARCH_RECV_RESP            462     //录像搜索接收数据 响应CMD(收)
#define REC_SEG_PLAYBACK_REQ                363     //录像回放CMD(发请求)
#define REC_SEG_PLAYBACK_RESP               463     //录像回放 响应CMD(收)
#define REC_SEG_GET_DATA_REQ                364     //录像媒体数据获取CMD(发请求)
#define REC_SEG_GET_DATA_FINISH             366     //结束录像媒体数据获取CMD(发请求)
#define CMD_WAIT_FOR_DATA_REG               460     //等待响应CMD(收)

//声网相关
#define CMD_AGORA_VIDEO_START                  303   //请求数据
#define CMD_AGORA_HEART_PACKAGE                999   //发送心跳包
#define CMD_AGORA_CHANGE_STREAM                305   //标高清切换

//MARK: 录像回放数据类型
#define PACKET_TYPE_MEDIA                   0x7F    //媒体包(值:127)
#define PACKET_TYPE_PARAM                   0x1F    //参数传输包(值:31)
#define PACKET_TYPE_ALIVE                   0x6F    //心跳等待包(值:111)
#define PACKET_TYPE_FINISH                  0xEF    //数据发送完毕通知包(值:239)

//MARK: 媒体包标识
#define PACKET_FLAG_EMPTY                   0x0F    //空包标志
#define PACKET_FLAG_END                     0xFF    //结束包标志
#define PACKET_FLAG_CURRENT_FILE_END        0xEF    //当前文件结束标志

//MARK: 设备录像状态
#define NV_RECORD_ENABLE                    1100    //录像开启
#define NV_RECORD_DISABLE                   1200    //录像关闭

//MARK: 云盘录像回放CMD
#define PB_CMD_REQUEST                      200     //云盘录像回放CMD(发请求)
#define PB_CMD_RESPONSE                     300     //云盘录像回放 响应CMD(收)
#define PB_CMD_GET_DATA_REQ                 201     //云盘录像回放数据获取CMD(发请求)
#define PB_CMD_GET_DATA_FINISH              202     //云盘录像回放数据获取 响应CMD(收)
#define PB_CMD_GET_EPITOME_DATA_REQ         203     // 云盘录像回放缩影数据cmd

#define PB_CMD_REQUEST_ALARM               201 //云盘录像关联CMD(发请求)
#define PB_CMD_RESPONSE_ALARM              301 //云盘录像关联回放 响应CMD(收)

//MARK: 云盘录像回放V2
#define PB_CMD_REQUEST_V2                  203 // 当天不间断播放请求
#define PB_CMD_RESPONSE_V2                 303 // 当天不间断播放响应

#define PB_CMD_REQUEST_EPITOME_V2          202 // 延时缩影V2
#define PB_CMD_RESPONSE_EPITOME_V2         302 // 延时缩影V2

#define PB_CMD_GET_DATA_EPITOME_V2         204 // 延时缩影V2

//MARK: 回放录像下载相关
#define PLAYBACK_ACK_REC_PACKET_COUNT_DOWNLOAD  1000    //512 byte*100 = 5k
#define PLAYBACK_ACK_REC_PACKET_COUNT           200     //512 byte*100 = 5k
#define ACTION_VALUE_POSITIONING_TIME           0x01    //定位时间，服务端收到该指令后需要定位到PlayStartTime指定的时间进行返回数据
#define ACTION_VALUE_ACK                        0x02    //包确认，当客户端收到约定的包数（RecvCount）后，确认收到的帧ID（RecvFrameID）
#define ACTION_VALUE_STOP                       0x03    //停止播放
#define ACTION_VALUE_RESEND                     0x04    //重发帧数据
#define PB_ACTION_ALARM                         0x05    // 根据报警图片时间戳定位播放
#define PB_ACTION_ALARM_RESEND                  0x06    // 报警图片重发帧数据

//MARK: 配网相关CMD
#define NV_IPC_CHECK_REQUEST                    372     //设备配网查询CMD(发请求)
#define NV_IPC_CHECK_RESPONSE                   472     //设备配网查询 响应CMD(收)

//MARK: 报警图片录像
#define REC_FILE_PLYBAK_ALARM                   153     //报警图片录像点播CMD(发请求)    根据报警信息
#define REC_PLAYBACK_RESP_ALARM                 253     //报警图片录像点播 响应CMD(收)   根据报警信息
#define PROGRESS_ALARM_RELATE                   1       //报警图片录像回放 第一帧数据
#define PROGRESS_DEFAULT                        0       //报警图片录像回放 非第一帧数据

//MARK: 音频对讲
#define NV_IPC_AUDIO_SPEAK                      180     //音频对讲
#define NV_IPC_ALIVE                            188     //心跳包

//MARK: 对讲
#define NV_IPC_CTRL_CONNECT_REQUEST             177     //对讲请求CMD(发送请求)
#define NV_IPC_CTRL_CONNECT_RESPONE             277     //对讲请求 响应CMD(收)
#define NV_IPC_CTRL_CONNECT_REQUEST_V20         377     //对讲请求CMD(发送请求 V20)
#define NV_IPC_CTRL_CONNECT_RESPONE_V20         477     //对讲请求 响应CMD(收 V20)

//MARK: 自定义报警语音 add by qin 20200609
#define NV_ALARM_AUDIO_REQUEST                  350     //自定义报警语音请求CMD（移动侦测）
#define NV_ALARM_AUDIO_REQUEST_AIHUMAN          352     //自定义报警语音请求CMD（AI人形报警）
#define NV_ALARM_AUDIO_RESPONE                  450     //自定义报警语音响应CMD（移动侦测）
#define NV_ALARM_AUDIO_RESPONE_AIHUMAN          452     //自定义报警语音响应CMD（AI人形报警）
#define NV_ALARM_AUDIO_REQUEST_LINE             351     //自定义报警语音请求CMD（越界报警
#define NV_ALARM_AUDIO_RESPONE_LINE             451     //自定义报警语音响应CMD（越界报警）
#define NV_ALARM_AUDIO_SEND                     181     //报警语音发送指令CMD
#define NV_ALARM_AUDIO_COMFIRM                  281     //确认指令CMD
#define NV_ALARM_AUDIO_SERVER_REQUEST           161     //互联网自定义报警语音请求CMD

//MARK: 白灯光设置 add by qin 20200718
#define NV_IPC_WHITE_LIGHT_CTRL_REQUEST         375     //白光灯设置请求指令CMD
#define NV_IPC_WHITE_LIGHT_CTRL_RESPONSE        475     //白光灯设置响应指令CMD

//MARK:时光相册
#define NV_IPC_CLOUD_TIME_LAPSE_VIDEO_GET_REQUEST 388 //时间相册配置获取请求CMD
#define NV_IPC_CLOUD_TIME_LAPSE_VIDEO_SET_REQUEST 389 ///时间相册配置设置请求CMD
#define NV_IPC_CLOUD_TIME_LAPSE_VIDEO_SET_RESPONE 489 ///时间相册配置设置响应CMD

//MARK: 镜头自动调焦
#define NV_IPC_SET_FOCAL_LENGTH                 376   //镜头自动调焦开始设置请求指令
#define NV_IPC_SET_FOCAL_LENGTH_RESPONSE        476  //镜头自动调焦开始设置返回指令

//MARK: 双目校准获取
#define NV_IPC_CAM_OFFSET_CTRL_GET_REQUEST        392  //双/多目镜头获取请求指令
#define NV_IPC_CAM_OFFSET_CTRL_GET_RESPONSE       492  //双/多目镜头获取返回指令
#define NV_IPC_CAM_OFFSET_CTRL_SET_REQUEST        393  //双/多目镜头设置请求指令
#define NV_IPC_CAM_OFFSET_CTRL_SET_RESPONSE       493  //双/多目镜头设置返回指令
#define NV_IPC_CAM_OFFSET_GET_SCREENSHOT          394  //获取截图指令请求指令
#define NV_IPC_CAM_OFFSET_GET_SCREENSHOT_RESPONSE 494  //获取截图指令返回指令

//MARK:  枪球联动设置
#define NV_IPC_CAM_LINKAGE_CALIBRATE_REQUEST 395                // 枪球联动设置请求指令
#define NV_IPC_CAM_LINKAGE_CALIBRATE_RESPONSE 495               //枪球联动设置返回指令
#define NV_IPC_CAM_ENTER_EXIT_LINKAGE_CALIBRATE_REQUEST 396     //进入/退出枪球联动设置请求指令
#define NV_IPC_CAM_ENTER_EXIT_LINKAGE_CALIBRATE_RESPONSE 496    // 进入/退出枪球联动设置返回指令

//MARK:查询云台自检状态
#define NV_IPC_CAM_PTZ_AUTO_DETECTION_REQUEST    397 //查询云台自检状态请求指令
#define NV_IPC_CAM_PTZ_AUTO_DETECTION_RESPONSE   497 //查询云台自检状态请求指令

//登录设备错误描述
#define LOGIN_CONNET_FAIL       101      //连接失败，未能成功连接到服务器（包括发送参数失败）
#define LOGIN_RECV_FAIL         102      //接收失败，接收服务器返回结果失败
#define LOGIN_ERROR_RESULT      103      //收到错误码，服务器有响应但是返回了一个错误码

//MARK: 灯光灵敏度
#define NV_IPC_X_PARAM_GET_REQUEST_EX           347     //灯光灵敏度获取CMD(发请求)
#define NV_IPC_X_PARAM_GET_RESPONSE_EX          447     //灯光灵敏度获取 响应CMD(收)
#define NV_IPC_X_PARAM_SET_REQUEST_EX           348     //设置灯光灵敏度CMD(发请求)
#define NV_IPC_X_PARAM_SET_RESPONSE_EX          448     //设置灯光灵敏度 响应CMD(收)

//MARK: 镜头图像方向
#define NV_IPC_CAM_ORENTATION                   190     //设置镜头图像方向CMD(发请求)

//MARK: 预览
#define CMD_MR_PLAY                             1002    //预览请求CMD(发请求)
#define CMD_MR_PLAY_RESPONSE                    2002    //预览请求 响应CMD(收)
#define CMD_MR_GET_IMAGE                        1003    //预览图像数据请求CMD(发请求)

//MARK: 对讲
#define CMD_CONTROL_CONNECT_REQUEST_MR          1011    //对讲连接CMD(发请求 互联网)
#define CMD_CONTROL_CONNECT_RESPONSE_MR         2011    //对讲连接 响应CMD(收 互联网)
#define CMD_SPEAK_CONTROL_MR                    1013    //对讲CMD(发请求 互联网)

//MARK: 录像回放
#define CMD_REC_FILE_SEARCH_MR                  1015    //录像回放搜索CMD(发请求 互联网)
#define CMD_REC_FILE_SEARCH_RESULT_MR           2015    //录像回放搜索 响应CMD(收 互联网)
#define CMD_REC_FILE_PLAYBACK_MR                1016    //录像回放CMD(发请求 互联网)
#define CMD_REC_FILE_PLAYBACK_RESPONSE_MR       2016    //录像回放 响应CMD(收 互联网)

//MARK: 录像回放登录(deprecate)
#define CMD_LOGIN_EX_MR                         1017    //录像回放登录CMD(发请求 互联网) deprecate
#define CMD_LOGIN_EX_RESULT_MR                  2017    //录像回放登录 响应CMD(收 互联网) deprecate
#define REC_FILE_PLAYBACK_GET_DATA_MR           1018    //录像回放数据数据获取CMD(发请求 互联网)
#define REC_FILE_PLAYBACK_FINISH_MR             2018    //录像回放数据数据获取 响应CMD(收 互联网)

//MARK: 声音开关
#define AUDIO_ENABLE_ON                 1000    //声音开启
#define AUDIO_ENABLE_OFF                1001    //声音关闭

//MARK: 推送相关
#define T_MSG_ALARM                     1       //推送消息类型 报警信息
#define T_MSG_AD                        2       //推送消息类型 广告信息
#define T_MSG_STAT                      3       //推送消息类型 设备状态信息

//MARK: 报警图片相关
#define CMD_ALARM_PIC_GET               8004    //获取报警图片握手CMD(发请求)
#define CMD_ALARM_PIC_GET_RESPONSE      8005    //获取报警图片握手 响应CMD(收)
#define CMD_ALARM_PIC_RECV_READY        8006    //获取报警图片CMD(发请求)
#define PACKET_FLAG_PICTURE             0xA1    //图片数据包
#define PACKET_FLAG_POSITION            0xA2    //坐标数据包

//MARK: 日志收集
#define MT_APP_LOGIN            10001    //登录设备
#define MT_APP_PREVIEW          10002    //实时预览
#define MT_APP_ONLINESTATE      10003    //查询在线状态
#define MT_APP_SERVICES         10004    //云服务绑定
#define MT_APP_UPDATE           10005    //APP更新
#define MT_APP_CRASH            10006    //APP崩溃
#define MT_APP_BEHAVIOR         10007    //用户行为

//MARK: 在线状态检测
#define NV_IPC_ONLINE_CHECK_REQUEST             172     //在线状态检测CMD(发请求)
#define NV_IPC_ONLINE_CHECK_RESPONSE            272     //在线状态检测 响应CMD(收)

//MARK: 门铃快速回复
#define NV_IPC_QUICK_RESPONSE_SET_REQUEST 387 //快速回复设置请求指令
#define NV_IPC_QUICK_RESPONSE_SET_RESPONSE 487 //快速回复设置返回指令
