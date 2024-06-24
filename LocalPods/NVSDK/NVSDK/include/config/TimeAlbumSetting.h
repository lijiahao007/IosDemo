//
//  TimeAlbumSetting.h
//  NVSDK
//
//  Created by master on 2022/9/26.
//  Copyright © 2022 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LoginHandle.h"
#import "TimeAlbumInfo.h"
NS_ASSUME_NONNULL_BEGIN

typedef enum : NSUInteger {
    DownloadStatusStart,
    DownloadStatusDownloading,
    DownloadStatusFinish,
    DownloadStatusError,
    
} DownloadStatus;

@protocol DownloadDelegate <NSObject>
@optional
-(void)onProgressChange:(int) nProgress status:(DownloadStatus)status;
@end

@interface TimeAlbumSetting : NSObject
+(void)cancelConfig;
+(int)setTimeAlbumConfig:(NVDevice *)device handle:(LoginHandle *)lHandle config:(TimeAlbumInfo *)info;

@property (assign) id<DownloadDelegate> downloadDelegate;
-(void)setTotalSize:(long long)totalSize;
-(void)addFileSizes:(NSArray*)sizes;
-(void)setVideoParam:(int)avType frameRate:(int)frameRate path:(NSString *)path;
-(int)putVideoData:(unsigned char *)data size:(int)lenght;
-(void)stopWrite:(BOOL)save;
- (BOOL)cleanAllFileInTempPath;

/**保存成功，返回结果等于lenght**/
-(int)putDataToQuaua:(unsigned char *)data size:(int)lenght;

-(NSData *)getDataFromQuaua:(int)lenght;
@end

NS_ASSUME_NONNULL_END
