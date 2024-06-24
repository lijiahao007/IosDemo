//
//  NVSDKLog.h
//  NVSDK
//
//  Created by caffe on 2019/9/26.
//  Copyright © 2019 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

//MARK: - 日志收集定义
/*
    logArray日志信息数组: 内部为一个字典
        字典格式:
            ### 基本信息
            IP:     地址;
            PORT:   端口号;
            CMD:    指令字;
 
            ### socket失败时 (与socket成功时互斥)
            FAIL:   socket失败函数(send或recv);
            IRET:   send或recv数值;
            
            ### socket成功时 (与socket失败时互斥)
            RESULT: 结果;
            VALUE:  结果描述.
*/
#define LOG_IP              @"ip"
#define LOG_PORT            @"port"
#define LOG_CMD             @"cmd"
//soecket失败
#define LOG_FAIL            @"fail"
#define LOG_IRET            @"iret"
//socket成功
#define LOG_RESULT          @"result"
#define LOG_VALUE           @"value"

typedef enum : NSUInteger {
    Log_Error_Code_Send_Fail        = 101,//socket发送失败
    Log_Error_Code_Recv_Fail        = 102,//socket接收失败
    Log_Error_Code_Response_Error   = 103,//收到服务器不正确结果
    
    //用于预览日志数据
    Log_Error_Code_Preview_Begin_Time = 1000,//开始时间
    Log_Error_Code_Clear_Preview_Logs = 1001,//清空日志
} Log_Error_Code;

NS_ASSUME_NONNULL_BEGIN

@interface NVSDKLog : NSObject
//MARK: - 登录日志
+ (void) disposeLoginLogList:(NSArray*)logList;//SDK内部使用
+ (NSArray*) getLoginLogList;

//MARK: - 在线状态日志
+ (void) disposeDeviceStatusCheckLogList:(NSArray*)logList;//SDK内部使用
+ (NSMutableArray*) getDeviceStatusCheckLogList;

//MARK: - 预览出图日志
//SDK内部使用: formatPreviewLogs()
+ (void) formatPreviewLogs:(NSString*)ip
                      port:(int)port
                       cmd:(int)cmd
                      type:(Log_Error_Code)type
                   content:(NSString*)content
               description:(NSString*)description;
+ (NSArray*) getPreviewLogList;
@end

NS_ASSUME_NONNULL_END
