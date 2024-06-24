//
//  NetworkConfigInfo.h
//  NVSDK
//
//  Created by caffe on 2019/2/22.
//  certified by caffe on 20190323
//  Copyright © 2019 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NetworkConfigInfo : NSObject
@property (assign) int nWifiMode;
@property (assign) int nResult;
@property (copy) NSString *strAPName;
@property (copy) NSString *strAPPassword;

@property (copy) NSString *strStationName;
@property (copy) NSString *strStationPassword;

-(BOOL)checkSaveAcount:(int)nDevID usr:(NSString *)strSUsername pwd:(NSString *)strSPassword;
@end

NS_ASSUME_NONNULL_END
