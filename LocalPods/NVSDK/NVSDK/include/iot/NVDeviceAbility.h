//
//  NVDeviceAbility.h
//  NVSDK
//
//  Created by HS on 2022/11/17.
//  Copyright © 2022 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "DeviceAbilityDefinition.h"
#import "LoginHandle.h"
#import "NVDeviceConfigInfo.h"

NS_ASSUME_NONNULL_BEGIN

@interface NVDeviceAbility : NSObject
@property(nonatomic, assign)int result;
@property (nonatomic,assign) int origin; //是否原始Lanpass：0=已更改；1=原始
@property(nonatomic, strong)NSDictionary *abilityDic;
@property(nonatomic, assign)_stream_ability streamAbility;//流能力集
@property(nonatomic, assign)_image_ability imageAbility;//图像能力集
@property(nonatomic, assign)_ctrl_ability ctrlAbility;//控制能力集
@property(nonatomic, assign)_light_ability lightAbility;//灯类能力集
@property(nonatomic, assign)_net_ability netAbility;//网络能力集
@property(nonatomic, assign)_alert_ability alertAbility;//报警能力集
@property(nonatomic, assign)_misc_ability miscAbility;//杂项能力值

//从获取设备能力请求的响应体中"data"字段数据中解析能力集
-(void)setAbility:(NSDictionary *)dic;

@end

NS_ASSUME_NONNULL_END
