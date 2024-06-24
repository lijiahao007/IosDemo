//
//  JsonUtil.h
//  iCamSee
//
//  Created by Macrovideo on 2021/10/19.
//  Copyright © 2021 Macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JsonUtils : NSObject

+(NSString *)dictionaryToJson:(NSDictionary *)dict;

+ (NSMutableString *)paramStringWithApiKey:(NSString *)apiKey infoDict:(NSDictionary *)dict;

//urlEncode编码
+(NSString *)urlEncodeStr:(NSString *)input ;
//urlEncode解码
+(NSString *)decoderUrlEncodeStr:(NSString *)input;
@end

NS_ASSUME_NONNULL_END
