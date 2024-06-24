//
//  MultiPlayer.h
//  NVSDK
//
//  Created by VINSON on 2019/11/27.
//  Copyright © 2019 macrovideo. All rights reserved.
//

/**
 FIXME: 接口设计有误
 PreviewEvents中的previewWifiStrength、previewBatteryRemaining、previewThermalMinTemperature、previewPTZXCruiseType，
 都是基于「playerBase: name: info:」的事件回调解析的，其实不应该在这里做这层解析，应该直接返回上层，
 以免后续有扩展还要新增解析
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "LoginHandle.h"



#define PREVIEW_PARAM_USERNAME      @"UserName"
#define PREVIEW_PARAM_PASSWORD      @"Password"
#define PREVIEW_PARAM_LANIP         @"LanIP"
#define PREVIEW_PARAM_NETIPARRAY    @"NetIPArray"
#define PREVIEW_PARAM_PORT          @"Port"
#define PREVIEW_PARAM_STREAM_TYPE      @"StreamType"
#define PREVIEW_PARAM_DEIVCEID      @"DeviceID"
#define PREVIEW_PARAM_CHANNEL       @"Channel"
#define PREVIEW_PARAM_STREAM_TYPE   @"StreamType"
#define PREVIEW_PARAM_IS_MUTED      @"IsMuted"
#define PREVIEW_PARAM_VIEW          @"View"

#define PREVIEW_PARAM_CAM_MODE      @"CAM_MODE"
#define PREVIEW_PARAM_IS_DOUL_CHANNEL      @"IsDoulChannel"
#define PREVIEW_PARAM_DOUL_MODE_TYPE      @"DoulModeType"
#define PREVIEW_PARAM_PICINPIC_MODE      @"PicInPicMode"
#define PREVIEW_PARAM_PICINPIC_X      @"PicInPicX"
#define PREVIEW_PARAM_PICINPIC_Y      @"PicInPicY"
#define PREVIEW_PARAM_PICINPIC_WIDTH      @"PicInPicWidth"
#define PREVIEW_PARAM_PICINPIC_HEIGHT      @"PicInPicHeight"
#define PREVIEW_PARAM_MAIN_CHANNEL_INDEX   @"MainChannelIndex"
#define PREVIEW_PARAM_SUB_CHANNEL_INDEX    @"SubChannelIndex"
#define PREVIEW_PARAM_STRETCH    @"stretch"

#define PREVIEW_PARAM_ACCOUNT        @"AccountID"
#define PREVIEW_PARAM_METHOD         @"Method"
#define PREVIEW_PARAM_FIRST_HANDLE   @"FirstHandle"
#define PREVIEW_PARAM_SUB_SERVER   @"SubServer"


NS_ASSUME_NONNULL_BEGIN

typedef enum : NSUInteger {
    MultiPlayerErrorEmptyPassword,
    MultiPlayerErrorUsernameOrPasswordIncorrect,
    MultiPlayerErrorLoginFailure,
    MultiPlayerErrorWeakPassword,
    MultiPlayerErrorNotAuthority
} MultiPlayerErrorCode;

typedef enum : NSUInteger {
    MultiPlayerState_Playing,
    MultiPlayerState_Stopped,
    MultiPlayerState_Paused,
    MultiPlayerState_Buffering,
    MultiPlayerState_Connecting,
} MultiPlayerState;

@protocol PreviewEvents <NSObject>
- (void) previewIdle:(BOOL)isIdle userInfo:(nullable id)userInfo atIndex:(int)index;
- (void) previewCameraType:(int)cameraType timestamp:(int64_t)timestamp width:(int)width height:(int)height userInfo:(nullable id)userInfo atIndex:(int)index;
- (void) previewLoginHandle:(LoginHandle*)handle loginError:(NSError*)error userInfo:(nullable id)userInfo atIndex:(int)index;
- (void) previewOldState:(MultiPlayerState)oldState newState:(MultiPlayerState)newState userInfo:(nullable id)userInfo atIndex:(int)index;
- (void) previewInfoName:(NSString*)name data:(NSDictionary*)data userInfo:(nullable id)userInfo atIndex:(int)index;// 归一化额外信息返回
- (void) previewStream:(int)stream atIndex:(int)index;
- (void) multiPreviewPanGesture:(UIPanGestureRecognizer*)recognizer;
- (void) multiPreviewDoubleTapGesture:(UITapGestureRecognizer*)recognizer;

@optional
- (void) previewWifiStrength:(int)strength wifiDB:(int)db userInfo:(nullable id)userInfo atIndex:(int)index __attribute__((deprecated("已废弃，请使用previewInfoName")));
@optional
- (void) previewBatteryRemaining:(int)remaining userInfo:(nullable id)userInfo atIndex:(int)index __attribute__((deprecated("已废弃，请使用previewInfoName")));
@optional
- (void) previewThermalMinTemperature:(int)min maxTemperature:(int)max FTempEnable:(BOOL)FTempEnable userInfo:(nullable id)userInfo atIndex:(int)index __attribute__((deprecated("已废弃，请使用previewInfoName")));
@optional
- (void) previewPTZXCruiseType:(int)type state:(int)state ptzxid:(int)ptzxid userInfo:(nullable id)userInfo atIndex:(int)index __attribute__((deprecated("已废弃，请使用previewInfoName")));
@optional
- (void) previewLensControl:(int)scaleCount scaleValue:(int)scaleValue scaleCurrent:(int)scaleCurrent userInfo:(nullable id)userInfo atIndex:(int)index __attribute__((deprecated("已废弃，请使用previewInfoName")));//add by qin 20201210
@end

@protocol MultiPreviewEvents <NSObject>
- (BOOL) multiPreviewCanSelectedAtIndex:(int)index;
- (BOOL) multiPreviewCanPanoONAtIndex:(int)index;
- (BOOL) multiPreviewCanPanoOFFAtIndex:(int)index;
- (void) multiPreviewCurrentSelected:(int)current previousSelected:(int)previous;
- (void) multiPreviewPanoON:(BOOL)on atIndex:(int)index;
- (void) multiPreviewPanoTouch:(CGPoint)point;
- (void) multiPreviewPINPSelected;
@end

@interface MultiPreviewPlayer : NSObject
@property (nonatomic,assign) int currentSelected;
@property (nonatomic,assign) int currentPano;
@property (nonatomic,strong,readonly) UIView *view;
@property (nonatomic,weak,nullable) id<PreviewEvents> previewEvents;
@property (nonatomic,weak,nullable) id<MultiPreviewEvents> multiPreviewEvents;

-(void)resetRowColumn:(BOOL)multi;      // 重置行数和列数 YES:2x2 NO:1*1(请慎用,尽量不要多次重复调用)
-(void)resetData:(int)index;            // 对全景库显示数据reset
-(void)resetDataAll;
-(void)setPanoHoldon:(BOOL)holdon;//是否禁止双击

-(BOOL)stop:(int)index;
-(void)stopAll;
-(void)active:(BOOL)active;
-(void)repaint;
-(void)clearSurface;
-(void)refix;
-(void)resetPanoBuffer;

-(void)allStretch:(BOOL)stretch;
-(void)stretch:(BOOL)stretch atIndex:(int)index;
-(void)mute:(BOOL)mute atIndex:(int)index;
-(void)reverse:(int)index;
-(void)light:(int)light atIndex:(int)index;
-(void)alarm:(int)action value:(int)value atIndex:(int)index;

-(void)imgset:(int)imgset starlight:(int)starlight atIndex:(int)index;
-(void)zoom:(int)zoom step:(int)step atIndex:(int)index;
-(void)moveTrack:(int)track state:(int)state channel:(int)channel atIndex:(int)index;
-(void)ptzWithUp:(BOOL)up left:(BOOL)left down:(BOOL)down right:(BOOL)right channel:(int)channel atIndex:(int)index;
-(BOOL)resetPTZX:(int)ptzxID atIndex:(int)index action:(int)action channel:(int)channel;
-(void)deletePTZX:(NSArray *)ptzxIDs atIndex:(int)index;

-(void)callPTZX:(int)ptzxID action:(int)action channel:(int)channel atIndex:(int)index;
-(UIImage*)srceenShot:(int)index;
-(UIImage*)srceenShotFromView;
-(void)thermal:(BOOL)thermal atIndex:(int)index;
-(void)linkage:(int)pointX value:(int)pointY atIndex:(int)index; //枪球联动设置

/**
 @param audio 是否需要发送音频json信息 （发过可以不发）(采样率等)
 @param video 是否需要发送视频json信息 （发过可以不发）(视频编码、宽高等)
 */
-(void)requestCallAtIndex:(int)index withAudio:(BOOL)audio withVideo:(BOOL)video callId:(NSNumber* __nullable)callId;

/**
 @param audio 是否需要发送音频停止信息 （发过可以不发）
 @param video 是否需要发送视频停止信息 （发过可以不发）
 */
-(void)requestHangupAtIndex:(int)index withAudio:(BOOL)audio withVideo:(BOOL)video callId:(NSNumber* __nullable)callId;

//add by luo 20231111
-(BOOL)turnVideoON:(BOOL)videoOn frame:(CGRect) viewPosition  onView:(UIView *) fView atIndex:(int)index;
-(BOOL)switchCamera;

-(BOOL)startRecord:(int)index videoPath:(NSString*)videoPath imagePath:(NSString*)imagePath;
-(BOOL)stopRecord:(BOOL)save atIndex:(int)index;
-(nullable NSError*)startTalk:(int)index;
-(nullable NSError*)startTalk:(int)index enableTwoWayTalk:(BOOL)enableTwoWayTalk;
-(void)stopTalk:(int)index;

-(void)pano:(BOOL)pano;
-(void)panoMode:(int)mode atIndex:(int)index;
-(void)panoType:(int)type atIndex:(int)index;  // 0:吊顶 1:壁挂

-(void)updatePanoParamWithConvert:(BOOL)convert atIndex:(int)index;

-(void)panoRectZoom;
-(void)panoRectResetZoom;
-(CGFloat)panoRectGetZoom;
-(void)isZoomScaleDisabled:(BOOL)disable;
-(void)setLinkageModeZoomDisabled:(BOOL)disable atIndex:(int)index;
-(void)installPanGesture:(BOOL)install;

-(void)changeStreamID:(int)stream index:(int)index;

-(void)panoRectSetZoom:(CGFloat)scale;

-(void)releaseAgora;

//IOT 3.0 新平台api
-(void)start:(int)index
       lanIP:(NSString*)lanIP
      netIPs:(NSArray<NSString*>*)netIPArray
        port:(int)port
      device:(NVDevice *)device
     channel:(int)channel
  streamType:(int)streamType
        mute:(BOOL)mute
     stretch:(BOOL)stretch
    userInfo:(nullable id)userInfo
      method:(NSString*)method
     accountId:(int)accountId;

- (BOOL)startLive:(id)param userInfo:(nullable id)userInfo atIndex:(int)index;
/**
 cameraMode:视频拼接类型
 subType:窗口显示模式
 */
-(void)setCameraMode:(int)cameraMode videoSplicing:(int)videoSplicing subType:(int)subType index:(int)index ;
- (BOOL)onDblClickView:(CGFloat)x y:(CGFloat)y;

@end

NS_ASSUME_NONNULL_END
