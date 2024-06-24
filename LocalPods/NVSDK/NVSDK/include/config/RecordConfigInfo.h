//
//  RecordConfigInfo.h
//  NVSDK
//
//  Created by caffe on 2019/2/22.
//  certified by caffe on 20190323
//  Copyright © 2019 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RecordConfigInfo : NSObject

@property (assign) int nRecordStat;
@property (assign) BOOL isNewVersion;
@property (assign) BOOL isAudioEnable;
@property (assign) int nFrameSize;

@property (assign) BOOL is1080PEnable;
@property (assign) BOOL is960PEnable;
@property (assign) BOOL is720PEnable;
@property (assign) BOOL isD1Enable;
@property (assign) BOOL isVGAEnable;
@property (assign) BOOL isCIFEnable;
@property (assign) BOOL isQVGAEnable;

@property (assign) int nResult;

@property (assign) int  nRecordFullDiskOP;
@property (assign) BOOL bAutoRecord;
@property (assign) BOOL bAlarmRecord;
@property (assign) int nDiskSize;
@property (assign) int nDiskRemainSize;

@property (assign) BOOL bCanFormat;

@property (copy) NSString *recordSharpness; //设备影子专用的清晰度设置

/**
 开启浓缩录像 0: not support 1:open 10: close
 */
@property (nonatomic,assign) int retrenRecordEnable;
/**
 当前浓缩录像时间间隔（单位为sec）
 */
@property (nonatomic,assign) int retrenchTime;
/**
 最小浓缩录像时间间隔（单位为sec）
 */
@property (nonatomic,assign) int minRetrenchTime;
/**
 最大浓缩录像时间间隔（单位为sec）
 */
@property (nonatomic,assign) int maxRetrenchTime;

-(BOOL)checkSaveAcount:(int)nDevID usr:(NSString *)strSUsername pwd:(NSString *)strSPassword;

/**
 是否存在SD卡
 */
-(BOOL) hasSDCard;

@end

NS_ASSUME_NONNULL_END
