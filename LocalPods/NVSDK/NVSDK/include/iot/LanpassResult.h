//
//  LanpassResult.h
//  NVSDK
//
//  Created by master on 2023/4/21.
//  Copyright © 2023 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface LanpassResult : NSObject
@property (nonatomic,assign) int resultCode;

@property (nonatomic,assign) int origin; //是否原始Lanpass：0=已更改；1=原始
@property (nonatomic,assign) int sid;    //临时sessionID
@property (nonatomic,assign) long perm;  //当前权限
@property (nonatomic, copy)NSString *devPublicKey; //设备端公钥数据
@property (nonatomic, copy)NSString *dS; //dK的验证数据

-(void)setVerifyResult:(NSDictionary*) dict;
@end

NS_ASSUME_NONNULL_END
