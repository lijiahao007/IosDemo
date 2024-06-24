//
//  LibContext.h
//  NVSDK
//
//  Created by macrovideo on 15/10/21.
//  Copyright © 2015年 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface LibContext : NSObject

#pragma mark ------ new sdk begin
+(BOOL) initResuorce;
+(BOOL) releaseResuorce;
#pragma mark ====== new sdk end

+(void)setZoneIndex:(int)nIndex;
+(int)getZoneIndex;
+(NSString*)sdkVersion;

#pragma mark --- old sdk begin
+(BOOL) InitResuorce;
+(BOOL) ReleaseResuorce;
#pragma mark === old sdk end
@end
