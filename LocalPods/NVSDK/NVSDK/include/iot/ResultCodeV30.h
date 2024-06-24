//
//  ResultCode.h
//  NVSDK
//
//  Created by Macrovideo on 2022/1/5.
//  Copyright © 2022 macrovideo. All rights reserved.
//

#ifndef ResultCodeV30_V30_h
#define ResultCodeV30_V30_h


#define RESULT_CODE_OK                         1000                 //服务器和设备共用返回，正常

#define RESULT_CODE_DEVICE_UNBOUND              1100                //设备返回，设备未绑定
#define RESULT_CODE_BOUND_BY_OTHER_USER         1101                //设备返回，设备已被其他账号绑定
#define RESULT_CODE_INVALID_COMMAND             1102                //设备返回，无效指令/无效方法
#define RESULT_CODE_PUBLIC_KEY_ERROR            1103                //设备返回，密钥交换key异常（一般是pubKey异常）
#define RESULT_CODE_SESSION_EXPIRED             1104                //设备返回，会话已过期/会话不存在
#define RESULT_CODE_DEVICE_ID_ERROR             1105                //设备返回，设备ID不匹配
#define RESULT_CODE_PARAM_ILLEGAL               1106                //设备返回，包含非法参数
#define RESULT_CODE_DEVICE_BUSY                 1107                //设备返回，设备繁忙
#define RESULT_CODE_CLIENT_UPPER_LIMIT          1108                //设备返回，访问客户端数量上限
#define RESULT_CODE_PERMISSIONS_ERROR           1109                //设备返回，权限不足
#define RESULT_CODE_NETWORK_NOT_SUPPORT_OPERATE 1110                //设备返回，当前网络模式不支持此操作
#define RESULT_CODE_REC_NOT_EXIST               1111                //设备返回，文件不存在
#define RESULT_CODE_CHANNEL_UNAVAILABLE         1112                //设备返回，设备通道不可用
#define RESULT_CODE_CHANNEL_NOT_SUPPORT_CHANGE  1113                //设备返回，设备通道不可变更（一般是已经指定过有效通道）
#define RESULT_CODE_PROPERTY_NOT_SUPPORT        1114                //设备返回，属性或操作不支持
#define RESULT_CODE_PROPERTY_READ_ONLY          1115                //设备返回，属性只读
#define RESULT_CODE_PROPERTY_VALUE_ERROR        1116                //设备返回，属性 value 错误（一般指类型）
#define RESULT_CODE_RESOURCES_NOT_ENOUGH        1117                //设备返回，资源不足（一般指内存）
#define RESULT_CODE_REFUSE_OPT_OR_DATA          1118                //设备返回，操作或数据被拒绝（不需要重试）
#define RESULT_CODE_VERIFICATION_CODE_ERROR     1119                //设备返回，验证码错误（配网发送pincode校验、lanpass）
#define RESULT_CODE_UNDEFINE_ERROR              2001                //设备返回，未定义错误


#define RESULT_ERR_SESSION_INVALID_HANDLE       1001                 //服务器返回，转发相关，无效session句柄
#define RESULT_ERR_SESSION_RUNNING              1002                 //服务器返回，转发相关，session句柄已被占用
#define RESULT_ERR_SESSION_INVALID_DEVICE_ID    1003                 //服务器返回，转发相关，设备ID无效
#define RESULT_ERR_SESSION_OTHER                1004                 //服务器返回，转发相关，关于session的其他错误
#define RESULT_ERR_CLIENT_INVALID               1010                 //服务器返回，转发相关，无效通道号
#define RESULT_ERR_CLIENT_RUNNING               1011                 //服务器返回，转发相关，该通道已被占用
#define RESULT_ERR_CLIENT_OTHER                 1012                 //服务器返回，转发相关，关于通道的其他错误

//MARK: 新平台临时保活
#define TMPKA_OK                    7400 //服务器返回，临时保活，成功
#define TMPKA_ERR_QUERY_PARAM       7401 //服务器返回，临时保活，无效的查询参数
#define TMPKA_ERR_SYSTEM            7402 //服务器返回，临时保活，系统错误
#define TMPKA_ERR_NOT_FOUND_IPC     7403 //服务器返回，临时保活，未找到设备
#define TMPKA_ERR_ABNORMAL_CONNECT  7404 //服务器返回，临时保活，设备异常
#define TMPKA_ERR_INVALID_TIMESTAMP 7405 //服务器返回，临时保活，无效时间戳
#define TMPKA_OK_FOUND_IPC          7406 //服务器返回，临时保活，找到设备

#endif /* ResultCode_h */
