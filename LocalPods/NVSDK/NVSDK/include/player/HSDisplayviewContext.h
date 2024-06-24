    //
    //  HSDisplayviewContext.h
    //  NVSDK
    //
    //  Created by mac on 2023/4/25.
    //  Copyright © 2023 macrovideo. All rights reserved.
    //

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface HSDisplayviewContext : NSObject
/**
 设置显示主模式(画面数量),参考HSDISPLAY_MODE
 */
+(void)setDisplayMode:(int) displayMode;
/**
 设置显示字模式（全景的各种模式、四画面子模式、枪球子模式）
 */
+(void)setDisplaySubMode:(int) mode;
/**
 设置窗口布局模式（如上下 ，左右，画中画等）[仅枪球DMODE_NORMAL_2X模式下]
 */
+(void)setSubViewType:(int)subType;
/**
 method:切换画中画位置
 @param picInpicMode:画中画的位置 参考enum PICNPIC_POSITION,当PICNPIC_SET_CUSTOM时需要后面的topX...，其他类型不需要
 */
+(BOOL)setPicInPicMode:(int)picInpicMode topX:(int) topX topY:(int)topY width:(int)width height:(int) height;
/**
 切换通道显示[0/1]
 */
+(void)setDoubleChannelMainWindowChn:(int)chn;
/**
 设置四画面是否能点击选中
 */
+(BOOL)isSubviewActive:(int) index;
+(void)setSubviewActive:(int) index ative:(BOOL) active;
/**
 判断画面点击是否点中画中画
 */
+(BOOL)isClickPinInPic:(CGFloat)x y:(CGFloat)y;
/**
 重置全屏效果
 */
+ (void)resetFullScreen;
/**
 重置画面缩放状态
 */
+ (void)resetZoom;
/**
 全景安装模式
 */
+(void)setPanoFixType:(int) fixType panoX: (int)panoX panoY: (int)panoY panoR:(int)panoR;
/**
 设置图像显示是否拉伸（是：拉伸填满显示窗口；否：匹配图像宽高比例）
 */
+(void)SetStretch:(BOOL) stretch;

+ (void)releasePanoView;
@end

NS_ASSUME_NONNULL_END
