//
//  VoiceGenerator.h
//  NVSDK
//
//  Created by package on 2024/5/27.
//  Copyright © 2024 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ToneGenerator : NSObject
+(ToneGenerator*) shareInstance;

/**
 生成info代表的音频，返回文件绝对路径
 */
-(NSString*) generatorWithMessage:(NSData*)info;

/**
 显示所有生成的音频文件
 */
-(NSArray*) getAllGeneratorFileAbsolutePath;

-(void) deleteAllGeneratorFile;

@end

NS_ASSUME_NONNULL_END
