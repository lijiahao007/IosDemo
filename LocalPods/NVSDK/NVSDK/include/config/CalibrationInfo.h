//
//  CalibrationInfo.h
//  NVSDK
//
//  Created by master on 2022/10/27.
//  Copyright © 2022 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


@interface CameraItem : NSObject<NSCopying>
/**
 镜头id：主镜头默认为0，其他镜头大于0
 */
@property (nonatomic ,assign) int cameraId;

/**
 镜头截图
 */
@property (nonatomic ,strong) UIImage *image;
/**
 镜头截图width
 */
@property (nonatomic ,assign) int width;
/**
 镜头截图height
 */
@property (nonatomic ,assign) int height;
/**
 中心点x偏移（在图像宽上的比例，精度为0.00001）eg: x偏移的像素值为 = x/width*10000
 */
@property (nonatomic ,assign) int offsetX;
/**
 中心点y偏移（在图像宽上的比例，精度为0.00001）eg: y偏移的像素值为 = y/height*10000
 */
@property (nonatomic ,assign) int offsetY;

@end


@interface CalibrationInfo : NSObject

@property (nonatomic ,assign) int nResult;
/**
镜头数量
 */
@property (nonatomic ,assign) int cameraCount;
/**
 偏移开关状态：01：开 10：关
 */
@property (nonatomic ,assign) int offsetSwitch;
/**
镜头信息
 */
@property (nonatomic ,strong) NSMutableArray *cameras;
/**
 操作：1=设置，2 = 取消对应镜头设置，3=取消全部镜头设置，4=仅设置偏移开关状态
 */
@property (nonatomic ,assign) int action;
@end

NS_ASSUME_NONNULL_END
