//
//  NVMediaPlayer.h
//  OpenGLES2ShaderRanderDemo
//
//  Created by cyh on 12. 11. 26..
//  Copyright (c) 2012년 cyh3813. All rights reserved.
//

#import <UIKit/UIKit.h>
//player
#import <AudioToolbox/AudioToolbox.h>
#import <AudioToolbox/AudioQueue.h>
#import "LoginHandle.h"
#import "RecordVideoInfo.h"
//#import "HYFisheyePanoView.h"
#import "NVPanoPlayer.h"
#import "PlaybackDelegate.h"

@protocol SingleGestureRecognizerDelegate <NSObject>
@optional
-(void)singleGestureRecognizer;

- (void) panoWidth:(short)width height:(short)height; //图像比例
- (void) panoViewTouch:(CGPoint)point; //点击
- (void) panoViewGesture:(UIPanGestureRecognizer*)recognizer; //拖动
- (void) panoViewDoubleTapGesture:(UITapGestureRecognizer*)recognizer;//双击
- (void) onPINPSelected;//画中画点击
@end

@interface NVPanoPlayer : UIView
@property (nonatomic,weak) id <SingleGestureRecognizerDelegate> singleDelegate;
@property (nonatomic, retain) UILabel *lblTimeOSD;

@property (copy, nonatomic) void (^wifiSignalBlock)(int level, short db);
@property (copy, nonatomic) void (^batteryVolumeBlock)(short volume);

//player
@property (assign) id<PlaybackDelegate> playbackDelegate;
@property (nonatomic,assign) CGFloat speed; // 回放倍速控制，stop的时候重置为1.0
@property (nonatomic,assign) BOOL stretch;
@property (nonatomic,assign,readonly) int frametype;
@property (nonatomic,assign) BOOL notReleasePanoWhenDealloc;
- (UIView *)view;
- (void)repaint;
-(void)resetData;
-(CGFloat)panoRectGetZoom;
-(void)panoRectResetZoom;
/**
 该接口目前只用作视频广场播放
 */
-(BOOL)startPlay:(int)nChn streamType:(int)nStreamType audio:(BOOL)bEnable loginHandel:(LoginHandle *)loginHandle;
-(BOOL)stopPlay;

/**
 TF卡回放
 */
-(BOOL)startPlayBack:(LoginHandle *)loginHandle file:(RecordVideoInfo *)recordVideo;
-(BOOL)startPlayBack:(LoginHandle *)loginHandle file:(RecordVideoInfo *)recordVideo speed:(CGFloat)speed;   // TF回放倍速播放接口
-(BOOL)stopPlayBack;
-(int)setPlayProgress:(int)progress;

/**
 云存储回放
 */
-(BOOL)startCloudPlayBack:(int)nAccountID devID:(int)nDeviceID pToken:(NSString *)strPToken sToken:(NSString *)strSToken ecsip:(NSString *)strIP ecsport:(int)nPort file:(RecordVideoInfo *)recFile loginhandle:(LoginHandle*)loginhandle;
-(BOOL)startCloudPlayBack:(int)nAccountID devID:(int)nDeviceID pToken:(NSString *)strPToken sToken:(NSString *)strSToken ecsip:(NSString *)strIP ecsport:(int)nPort file:(RecordVideoInfo *)recFile loginhandle:(LoginHandle*)loginhandle speed:(CGFloat)speed;
-(BOOL)stopCloudPlayBack;

/**
 报警关联视频回放
 */
-(BOOL)startAlarmVideoPlayBack:(int)nAccountID devID:(int)nDeviceID sToken:(NSString *)strSToken ecsip:(NSString *)strIP ecsport:(int)nPort vType:(int)vtype vid:(long long)vid vts:(long long)vts;
-(BOOL)startAlarmVideo:(NVDevice*)device alarmMessage:(AlarmMessage *)info sToken:(NSString *)strSToken doulChannelMode:(int)doulChannelMode;

/**
 云盘录像回放
 */
typedef struct _UCloudPlayback {
    int         tempAccountID;    //账户ID
    int         nDeviceID;        //设备ID
    NSString    *loginToken;      //账户登录token
    NSString    *strIP;           //服务器IP地址
    int         nPort;            //服务器端口号
    int         nChannel;         //回放通道号
    int         nFileID;          //回放文件信息
    long        startTimestamp;   //回放文件开始时间戳
    long        serverTimestamp;  //回放文件服务器保存时间
    int         secondsWerePlayed;
    int         cameraType;       //镜头类型
    int         nPanoX;           //全景校正参数X
    int         nPanoY;           //全景校正参数Y
    int         nPanoRad;         //全景校正参数R
    int        fileTotalTime;     //文件总时长
    int         vrand;  //随机数 （云盘录像关联使用）
    long        passMs;   //Start_MS到报警经历时间差 云盘录像关联使用）
    BOOL        isPlayDiskAlarm; //是否播放云盘关联录像
    BOOL        isPlayEpitome;  // 是否播放云盘缩影
    NSData    *shareKey; //新平台解密key
    BOOL      isDoulChannelMode;
}UCloudPlaybackParam;

-(BOOL)StartPlayBackUCloudWithParam:(UCloudPlaybackParam)param;
-(BOOL)StartPlayBackUCloudWithParam:(UCloudPlaybackParam)param speed:(CGFloat)speed keepSurface:(BOOL)keepSurface;

/**
 通用
 */
-(void)enableAudio:(BOOL)bEnable;
- (void)initFisheyeParam:(int)iFixType andCenterX:(int) xCenter andCenterY:(int)yCenter andRadius:(int)radius ;
- (void)setImageYUV:(int)RGBorYUV420 andImageBuffer:(Byte *) pData andWidth:(int) width andHeight:(int) height;
- (void)setMode:(int) iMode;
-(void)setCamType:(int)CamType;
- (void)clearsurface;//RGB图片预览下一张加载过程的清屏工作
- (void)setActive: (BOOL) bActive;
- (void)resetDataFlag;
- (void)resetPanoBuffer;
- (void)setIsOnback:(BOOL)onback; //预防有时候退出还能接收数据add by yang20200330
- (UIImage *)screenShot;  //截屏
- (UIImage *)screenShot2; //原始帧
- (void)onApplicationDidBecomeActive;
- (void)onApplicationWillResignActive;
- (void)timeIndexWhenPause: (int)pauseTimeIndex;
- (void)resetPause;
-(void)timeIndexChangePlayBackV30:(int)currentTime;//20190315 云盘用到，之前一直没有使用，都是直接StartPlayBackV30重新播放

/**
 * @brief    添加特定释放操作, 防止出现内存问题 或 定时器问题.
 *
 * 当前释放操作暴包括:
 * 1. 当前发现鱼眼库有一个定时器, 导致鱼眼库无法被释放;
 */

-(void)releaseAction;
/**
 新平台TF卡回放
 */
-(BOOL)startTFCardPlayBack:(NVDevice *)device file:(RecordVideoInfo *)recFile;
-(BOOL)stopTFCardPlayBack;

/**
 枪球设备功能
 */
/**
 method:设置是否联动设备
 @param isDoulChannelMode:是否枪球联动设备
 @param doulModeType:枪球联动显示模式
 DOUL_MODE_SEPARATE_VERTICAL 0  //单独上下显示
 DOUL_MODE_SEPARATE_HORIZONTAL 1  //单独左右显示
 DOUL_MODE_PICINPIC 2 //画中画
 DOUL_MODE_SINGLE_SCREEN 3 //单画面
 */
-(BOOL)setDoulMode:(int)isDoulChannelMode videoSplicing:(int)videoSplicing type:(int)doulModeType;
- (BOOL)onDblClickView:(CGFloat)x y:(CGFloat)y;

//主动调用手势操作
-(void) handlePinch:(UIPinchGestureRecognizer*)recognizer;
@end
