//
//  FilePlayerDelegate.h
//  NVSDK
//
//  Created by macrovideo on 19/03/2018.
//  Copyright © 2018 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol FilePlayerDelegate <NSObject>
#pragma Deprecated use onFileParamters
-(void)setFileParam:(int)nCamType panoX:(int) nPanoX panoY:(int) nPanoY panoRad:(int) nPanoRad timeLength:(int64_t) lTimeLength;
//func: onFileParamters
//param: fileParameter - NSDictionary
//        camType   : (int)
//        panoX     : (int)
//        panoY     : (int)
//        panoR     : (int)
//        duration  : 文件持续时间(int64_t)
//        doulChn   : 双流合并，抢球设备(int)
-(void)onProgressChange:(int) nProgress;
-(void)onTimeChange:(int64_t) lTimeCurrent;
@optional
-(void)onFileParamters:(id)fileParameter;
- (void) onPINPSelected;
- (void) panoViewDoubleTapGesture:(UITapGestureRecognizer*)recognizer;//双击
@end
