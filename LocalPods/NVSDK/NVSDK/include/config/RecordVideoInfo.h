//
//  RecordVideoInfo.h
//  NVSDK
//
//  Created by caffe on 2019/2/22.
//  certified by caffe 20190325
//  Copyright © 2019 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RecordVideoInfo : NSObject
@property (assign) int version;
@property (assign) int nFileID;
@property (assign) int nFileSize;
@property (copy) NSString *strFileName;
@property (assign) int nStartHour;
@property (assign) int nStartMin;
@property (assign) int nStartSec;
@property (assign) int nFileTimeLen;

@property (assign) int nDownloadStatus;
@property (assign) float nDownloadProcess;

@property (assign) int nfileType;
@property (assign) int nStartTime;
@property (assign) int nEndTime;
@property (assign) int nCurrentTime;//增属性，支持新协议 by weibin 20190225

@property (assign) long long nStartTimeMS;
@property (assign) long long nEndTimeMS;

@property (nonatomic, assign) int downloadEpitomeRate; // 浓缩录像下载帧率 （在APP中由用户设置）
@end

NS_ASSUME_NONNULL_END
