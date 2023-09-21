

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface HSColorUtils : NSObject

+ (UIColor* )colorWithRGB:(NSUInteger)rgb alpha:(CGFloat)alpha;
+ (UIColor* )colorWithRGB:(NSUInteger)rgb;
+ (UIColor *)colorWithSRGB:(NSString *)srgb;
+ (UIColor *)colorWithRGBString:(NSString *)rgb;

/**
 *  @brief 两种颜色中间的某个颜色
 *  @param progress 中间某个百分比
 */
+ (UIColor *)colorWithProgress:(CGFloat)progress fromColor:(UIColor *)fromColor toColor:(UIColor *)toColor;

/**
 *  @brief 两种颜色相似
 */
+ (BOOL)isColor:(UIColor* )color1 similarWith:(UIColor* )color2;

+ (void)gradientColors:(NSArray *)colors onView:(UIView *)view horizontal:(BOOL)isHorizontal;
+ (NSUInteger)rgbOfPoint:(CGPoint)point onLayer:(CALayer *)layer;
+ (NSInteger)rgbFromR:(NSInteger)r g:(NSInteger)r b:(NSInteger)r;
+ (NSUInteger)rgbFromColor:(UIColor *)color;
+ (CGFloat)alphaFromColor:(UIColor *)color;

@end

//绘制宽度为1像素的线
void draw1PxStroke(CGContextRef context, CGPoint startPoint, CGPoint endPoint, CGColorRef color);
//填充矩形区域
void fillRectWithColor(CGContextRef context, CGRect rectToFill, CGColorRef color);

@interface HSColorScheme : NSObject

+ (UIColor*)colorWithDarkMode:(UIColor*)darkColor lightColor:(UIColor*)lightColor;
+ (UIColor*)colorWithDarkModeRGB:(NSUInteger)darkColor lightColor:(NSUInteger)lightColor;
+ (UIColor*)colorForUserInterfaceStyle:(UIColor*)color userInterfaceStyle:(UIUserInterfaceStyle)userInterfaceStyle API_AVAILABLE(tvos(10.0)) API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos);

@property(class) UIColor* colorGreenLight;
@property(class) UIColor* colorGreenNormal;
@property(class) UIColor* colorGreenHeavy;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
@property(class) UIColor* colorGreen;
#pragma clang diagnostic pop

@property(class) UIColor* colorRedLight;
@property(class) UIColor* colorRedNormal;
@property(class) UIColor* colorRedHeavy;

@property(class) UIColor* colorBlue;//默认所有蓝色

@property(class) UIColor* colorWhite;
@property(class) UIColor* colorGrayLighter;
@property(class) UIColor* colorGrayLight;
@property(class) UIColor* colorGrayNormal;
@property(class) UIColor* colorGrayAbnormal;
@property(class) UIColor* colorGrayHeavy;
@property(class) UIColor* colorGrayHeavier;
@property(class) UIColor* colorBlack;

@property(class) UIColor* colorForeground;
@property(class) UIColor* colorBackground;
@property(class) UIColor* colorBackgroundWhite;

@property(class) UIColor* colorOverlayerBlack;

@property(class) UIColor* colorline;//分割线
@property(class) UIColor* colorTextTitle;//字体标题颜色

@property(class) UIColor* colorSecondary;//字体标题颜色
@end
