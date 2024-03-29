//
//  PermissionManager.m
//  iCamSee
//
//  Created by Macro-Video on 2020/12/22.
//  Copyright © 2020 Macrovideo. All rights reserved.
//

#import "PermissionManager.h"
#import <AVFoundation/AVFoundation.h>
#import <AssetsLibrary/AssetsLibrary.h>
#import <Photos/PHPhotoLibrary.h>
#import <CoreLocation/CoreLocation.h>
#import <Speech/Speech.h>
#import "AFNetworkReachabilityManager.h"
@interface PermissionManager()
@property (nonatomic, assign) BOOL networkReachabilityFlag; //是否检查过网络权限

@end

static PermissionManager *manager;

@implementation PermissionManager

#pragma mark - ----------------------------------------------检查定位权限----------------------------------------------

+(void)checkNetWorkPermission:(PermissionBlock)callBackBlock{
    if (manager == nil) {
        manager = [[PermissionManager alloc] init];
    }
    if (manager.networkReachabilityFlag == YES) {
        [self callBack:callBackBlock isAuthorized:YES];
        return;
    }
    manager.networkReachabilityFlag = YES;
    
    [[AFNetworkReachabilityManager sharedManager] setReachabilityStatusChangeBlock:^(AFNetworkReachabilityStatus status) {

        switch (status) {
            case AFNetworkReachabilityStatusReachableViaWiFi:
            case AFNetworkReachabilityStatusReachableViaWWAN:
                [self callBack:callBackBlock isAuthorized:YES];
                break;
            default:
            {
                NSString *title = NSLocalizedString(@"noNetwork", @"无网络连接");
                NSString *message = [NSString stringWithFormat:@"%@\n%@\n%@  %@",NSLocalizedString(@"probableCause", @"可能的原因:"),NSLocalizedString(@"noNetworkConnecting", @"1、手机未连接网络"),NSLocalizedString(@"noNetworkPermission", @"2、app没有权限访问网络。"),NSLocalizedString(@"toSetting", @"去设置")];
                
//                MVAlertController *alert = [[MVAlertController alloc] init];
//                [alert showAlertWithType:MVAlertControllerTypeOneAction title:title message:message handel:^{
//                }];
//                [alert setMessageAttributeTapActionStirng:NSLocalizedString(@"toSetting", @"去设置") dismissWhenTap:YES];
//                alert.delegate = manager;
//                [alert setMessageTextAlignment:NSTextAlignmentLeft];
////                [alert setMessageColor:HSColorScheme.colorBlack];
////                [alert setMessageFont:[UIFont systemFontOfSize:16]];
////                [alert setConfirmTitleColor:HSColorScheme.colorBlue];
////                [alert settingButtonBoderColor:HSColorScheme.colorline];
//                [alert setConfirmTitle:NSLocalizedString(@"btnIKonw", @"我知道了")];
//                
//                
                
                
                [self callBack:callBackBlock isAuthorized:NO];
            }
                break;
        }
        [[AFNetworkReachabilityManager sharedManager] stopMonitoring];
    }];
    [[AFNetworkReachabilityManager sharedManager] startMonitoring];
}

#pragma mark - ----------------------------------------------检查相机权限----------------------------------------------
+(void)checkCameraPermission:(PermissionBlock)callBackBlock{
    
    AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
    if(authStatus == AVAuthorizationStatusRestricted || authStatus == AVAuthorizationStatusDenied){
        //被用户拒绝或者没有权限 只能弹出提示让用户自己改
        [self showGoToSettingAlert:NSLocalizedString(@"speechRecognizerPermissionTips", @"请前往\"设置\" 为app打开相机权限后重新尝试")];
        [self callBack:callBackBlock isAuthorized:NO];
        
    }else if (authStatus == AVAuthorizationStatusNotDetermined){
        //还没有请求过
        [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {
            if (granted) {
                // 用户第一次同意了访问相机权限
                [self callBack:callBackBlock isAuthorized:YES];
            } else {
                // 用户第一次拒绝了访问相机权限
                [self callBack:callBackBlock isAuthorized:NO];
            }
        }];
        
    }else if (authStatus == AVAuthorizationStatusAuthorized){
        //允许
        [self callBack:callBackBlock isAuthorized:YES];
    }
}



#pragma mark - ----------------------------------------------检查相册权限----------------------------------------------
+(void)checkAlbumPermission:(PermissionBlock)callBackBlock{
    
    PHAuthorizationStatus authStatus = [PHPhotoLibrary authorizationStatus];
    if (@available(iOS 14, *)) {
        if (authStatus == PHAuthorizationStatusLimited) {
            //IOS14新增：有限授权：仅可访问用户指定的相册图片,目前的做法是默认识别为已取得授权，如果后续发现问题再改
            [self callBack:callBackBlock isAuthorized:YES];
            return;
        }
    }
    
    if (authStatus == PHAuthorizationStatusRestricted || authStatus == PHAuthorizationStatusDenied){
        //被用户拒绝或者没有权限 只能弹出提示让用户自己改
        [self showGoToSettingAlert:NSLocalizedString(@"locationPermissionTips", @"请前往\"设置\"为app打开相册权限后重新尝试")];
        [self callBack:callBackBlock isAuthorized:NO];
        
    }else if (authStatus == PHAuthorizationStatusNotDetermined){
        //还没有请求过
        [PHPhotoLibrary requestAuthorization:^(PHAuthorizationStatus status) {
//            XLog(@"status = %ld",(long)status);
            if (status == PHAuthorizationStatusAuthorized) {
                [self callBack:callBackBlock isAuthorized:YES];
            }else if (status == PHAuthorizationStatusDenied){
                [self callBack:callBackBlock isAuthorized:NO];
            }
        }];
        
    }else{
        //允许
        [self callBack:callBackBlock isAuthorized:YES];
    }
}


#pragma mark - ----------------------------------------------检查麦克风权限----------------------------------------------
+(void)checkRecordPermission:(PermissionBlock)callBackBlock{
    AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio];
    if(authStatus == AVAuthorizationStatusRestricted || authStatus == AVAuthorizationStatusDenied){
        //被用户拒绝或者没有权限 只能弹出提示让用户自己改
        [self showGoToSettingAlert:NSLocalizedString(@"recordPermissionTips", @"请前往\"设置\"为app打开麦克风权限后重新尝试")];
        [self callBack:callBackBlock isAuthorized:NO];
        
    }else if (authStatus == AVAuthorizationStatusNotDetermined){
        //还没有请求过
        [AVCaptureDevice requestAccessForMediaType:AVMediaTypeAudio completionHandler:^(BOOL granted) {
            if (granted) {
                // 用户第一次同意了访问麦克风权限
                [self callBack:callBackBlock isAuthorized:YES];
            } else {
                // 用户第一次拒绝了访问麦克风权限
                [self callBack:callBackBlock isAuthorized:NO];
            }
        }];
        
    }else if (authStatus == AVAuthorizationStatusAuthorized){
        //允许
        [self callBack:callBackBlock isAuthorized:YES];
    }
}


#pragma mark - ----------------------------------------------检查定位权限----------------------------------------------
+(void)checkLocationPermission:(PermissionBlock)callBackBlock{
    
    if ([[UIDevice currentDevice].systemVersion doubleValue] < 13.0) {
        [self callBack:callBackBlock isAuthorized:YES];
        return;
    }
    
    CLAuthorizationStatus authStatus = [CLLocationManager authorizationStatus];
    if(authStatus == kCLAuthorizationStatusRestricted || authStatus == kCLAuthorizationStatusDenied){
        //被用户拒绝或者没有权限 只能弹出提示让用户自己改
        [self showGoToSettingAlert:NSLocalizedString(@"albumPermissionTips", @"请前往\"设置\"为app打开定位权限后重新尝试")];
        [self callBack:callBackBlock isAuthorized:NO];
        
    }else if (authStatus == kCLAuthorizationStatusNotDetermined){
        //还没有请求过 由于定位权限的请求没有回调，所以无法得知用户是否授权定位，因此无法调用callBackBlock
        CLLocationManager *manager = [[CLLocationManager alloc] init];
        [manager requestWhenInUseAuthorization];
        
    }else if (authStatus == kCLAuthorizationStatusAuthorizedAlways || kCLAuthorizationStatusAuthorizedWhenInUse){
        //允许
        [self callBack:callBackBlock isAuthorized:YES];
    }
    
}


#pragma mark - ----------------------------------------------检查语音识别----------------------------------------------
+(void)checkSpeechRecognizerPermission:(PermissionBlock)callBackBlock{
    
    if (@available(iOS 10.0, *)) {
        SFSpeechRecognizerAuthorizationStatus status =  [SFSpeechRecognizer authorizationStatus];
        
        if(status == SFSpeechRecognizerAuthorizationStatusNotDetermined ){
            
            [SFSpeechRecognizer requestAuthorization:^(SFSpeechRecognizerAuthorizationStatus status) {
                switch (status) {
                    case SFSpeechRecognizerAuthorizationStatusNotDetermined:
                    case SFSpeechRecognizerAuthorizationStatusDenied:
                    case SFSpeechRecognizerAuthorizationStatusRestricted:
                        [self showGoToSettingAlert:NSLocalizedString(@"cameraPermissionTips", @"请前往\"设置\"为app打开语音识别权限后重新尝试")];
                        [self callBack:callBackBlock isAuthorized:NO];
                        break;
                    case SFSpeechRecognizerAuthorizationStatusAuthorized:        //已授权
                        [self callBack:callBackBlock isAuthorized:YES];
                        break;
                    default:
                        break;
                }
            }];
            
        }else if(status == SFSpeechRecognizerAuthorizationStatusDenied || status == SFSpeechRecognizerAuthorizationStatusRestricted ){
            [self showGoToSettingAlert:@"请前往“设置” 为app打开语音识别权限后重新尝试"];
            [self callBack:callBackBlock isAuthorized:NO];
            
        }else if(status == SFSpeechRecognizerAuthorizationStatusAuthorized){
            [self callBack:callBackBlock isAuthorized:YES];
        }
    }
}


#pragma mark - ---------------------------------------------------其他------------------------------------------------
+(void)showGoToSettingAlert:(NSString *)message{
//    dispatch_async(dispatch_get_main_queue(), ^{
//        MVAlertController *alert = [[MVAlertController alloc] init];
//        [alert showAlertWithType:MVAlertControllerTypeOKAndCancel title:NSLocalizedString(@"noPromiss", @"没有权限") message:message handel:^{
//            [self toSetting];
//        }];
//    });
}

+(void)toSetting{
    NSURL *url = [NSURL URLWithString:UIApplicationOpenSettingsURLString];
    if( [[UIApplication sharedApplication] canOpenURL:url]){
        [[UIApplication sharedApplication] openURL:url];
    }
}

+(void)callBack:(PermissionBlock)callBackBlock isAuthorized:(BOOL)isAuthorized{
    dispatch_async(dispatch_get_main_queue(), ^{
        callBackBlock(isAuthorized);
    });
    
}

#pragma mark - ---------------------------------------------------MVAlertDelegate------------------------------------------------
-(void)alertAttributeStringDidTap:(NSString *)string range:(NSRange)range{
    [PermissionManager toSetting];
}

@end
