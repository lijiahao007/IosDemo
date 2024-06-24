//
//  AlarmMessage.h
//  macroSEE
//
//  Created by macrovideo on 14-9-17.
//  Copyright (c) 2014年 cctv. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface AlarmMessage : NSObject

@property (assign) int nID;
@property (assign) long long nSaveID;//update by xie yongsheng 20180920
@property (assign) int nDevID;
@property (assign) int nAlarmType;
@property (assign) int nAlarmLevel;
@property (assign) long long llAlarmTime;
@property (copy) NSString *strAlarmContent;
@property (copy) NSString *strAccureTime;
@property (retain) UIImage *imageData;
@property (assign) BOOL hasPosition;//是否带人工智能
@property (copy) NSString *strImageIP;  //获取图片大图ip
@property (copy) NSString *imageDomain;//获取图片大图域名
@property (assign) long oss_id;
@property (assign) int ctype;
@property (assign) long cx;
@property (assign) long cy;
@property (assign) long cr;
@property (assign) int vtype;  //录像类型
@property (assign) long long vid;   //录像ID
@property (assign) long long vts;   //录像时间

/** 报警图片关联云盘录像新增*/
@property (assign) int uid;  //userID
@property (assign) int vrand; //videoRandNumber 随机数
@property (assign) int bidx;  // BucketIndex
@property (assign) int channel;  // channel

@property (assign) BOOL isThumbnail;  //是否缩略图

@property (nonatomic,assign) int platform;  //是否新平台
@property (nonatomic,assign) BOOL isBindCloud;  //是否绑定云服务
@property (nonatomic,assign) BOOL isBindAI;  //是否绑定AI

/**报警短视频 **/
@property (nonatomic,assign) int aformat; //0:报警图片 1:报警小视频
@property (nonatomic,assign) int videoCodec; //视频编码 mvdef_media_codec_e
@property (nonatomic,assign) int hasAudio; //是否有音频帧
@property (nonatomic,assign) int audioCodec; //音频编码 mvdef_media_codec_e
@property (nonatomic,assign) int sampleRate;
@property (nonatomic,assign) int sampleBits;
@property (nonatomic,assign) int audioChannel;
@property (nonatomic,assign) int width;
@property (nonatomic,assign) int height;
@property (nonatomic,assign) int videoSplicing; //视频拼接，0是非抢球不拼接
@property (nonatomic,assign) int msgEncoding; // 主动报警内容编码 (1:utf-8 0:其他)
@property (nonatomic,strong) NSString* msgContent; // 主动报警内容
@end
