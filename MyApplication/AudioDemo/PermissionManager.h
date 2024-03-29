//
//  PermissionManager.h
//  iCamSee
//
//  Created by Macro-Video on 2020/12/22.
//  Copyright © 2020 Macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^PermissionBlock)(BOOL isPermission);

@interface PermissionManager : NSObject
//检查网络权限
+(void)checkNetWorkPermission:(PermissionBlock)callBackBlock;
    
//检查相机权限
+(void)checkCameraPermission:(PermissionBlock)callBackBlock;

//检查相册权限
+(void)checkAlbumPermission:(PermissionBlock)callBackBlock;

//检查麦克风权限
+(void)checkRecordPermission:(PermissionBlock)callBackBlock;

//检查定位权限
+(void)checkLocationPermission:(PermissionBlock)callBackBlock;

//检查语音识别
+(void)checkSpeechRecognizerPermission:(PermissionBlock)callBackBlock;
@end

NS_ASSUME_NONNULL_END
