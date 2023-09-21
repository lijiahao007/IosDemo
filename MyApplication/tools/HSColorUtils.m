

#import "HSColorUtils.h"

@implementation HSColorUtils

+ (UIColor* )colorWithRGB:(NSUInteger)rgb alpha:(CGFloat)alpha
{
    CGFloat r = (CGFloat)( rgb <<  8 >> 24 & 0xFF ) / 255.0f;
    CGFloat g = (CGFloat)( rgb << 16 >> 24 & 0xFF ) / 255.0f;
    CGFloat b = (CGFloat)( rgb & 0xFF ) / 255.0f;
    
    return [UIColor colorWithRed:r green:g blue:b alpha:alpha];
}

+ (UIColor *)colorWithRGBString:(NSString *)rgb
{
    if ([rgb compare:@"clear" options:NSCaseInsensitiveSearch] == NSOrderedSame)
    {
        return [UIColor clearColor];
    }
    NSString *cString = [[rgb stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] uppercaseString];
    // String should be 6 or 8 charactersif ([cString length] < 6) return [UIColor blackColor];
    // strip 0X if it appearsif ([cString hasPrefix:@"0X"]) cString = [cString substringFromIndex:2];
    if ([cString hasPrefix:@"#"]) cString = [cString substringFromIndex:1];
    if ([cString length] != 6) return [UIColor blackColor];
    
    // Separate into r, g, b substrings
    NSRange range;
    range.location = 0;
    range.length = 2;
    NSString *rString = [cString substringWithRange:range];
    range.location = 2;
    NSString *gString = [cString substringWithRange:range];
    range.location = 4;
    NSString *bString = [cString substringWithRange:range];
    // Scan values
    unsigned int r, g, b;
    
    [[NSScanner scannerWithString:rString] scanHexInt:&r];
    [[NSScanner scannerWithString:gString] scanHexInt:&g];
    [[NSScanner scannerWithString:bString] scanHexInt:&b];
    
    return [UIColor colorWithRed:((float) r / 255.0f)
                           green:((float) g / 255.0f)
                            blue:((float) b / 255.0f)
                           alpha:1.0f];
}

+ (UIColor* )colorWithRGB:(NSUInteger)rgb
{
    return [self colorWithRGB:rgb alpha:1.0f];
}

+ (UIColor *)colorWithSRGB:(NSString *)srgb
{
    NSString* rgb = srgb;
    if ([srgb hasPrefix:@"#"]) {
        rgb = [srgb substringFromIndex:1];
    }
    unsigned int rgbint;
    NSScanner* scanner = [NSScanner scannerWithString:rgb];
    BOOL result = [scanner scanHexInt:&rgbint];
    if (result) {
        return [self colorWithRGB:rgbint];
    } else {
        return [UIColor clearColor];
    }
}

+ (UIColor *)colorWithProgress:(CGFloat)progress fromColor:(UIColor *)fromColor toColor:(UIColor *)toColor
{
    CGFloat r1, g1, b1, a1, r2, g2, b2, a2;
    [fromColor getRed:&r1 green:&g1 blue:&b1 alpha:&a1];
    [toColor getRed:&r2 green:&g2 blue:&b2 alpha:&a2];
    CGFloat r, g, b, a;
    r = (r2 - r1) * progress + r1;
    g = (g2 - g1) * progress + g1;
    b = (b2 - b1) * progress + b1;
    a = (a2 - a1) * progress + a1;
    return [UIColor colorWithRed:r green:g blue:b alpha:a];
}

+ (NSInteger)rgbFromR:(NSInteger)r g:(NSInteger)g b:(NSInteger)b {
    return (r << 16) + (g << 8) + b;
}

+ (NSUInteger)rgbFromColor:(UIColor *)color
{
    CGFloat r1,g1,b1;
    [color getRed:&r1 green:&g1 blue:&b1 alpha:nil];
    NSInteger rgb = [self rgbFromR:r1*255 g:g1*255 b:b1*255];
    return rgb;
}

+ (CGFloat)alphaFromColor:(UIColor *)color
{
    CGFloat alpha;
    [color getRed:NULL green:NULL blue:NULL alpha:&alpha];
    return alpha;
}

+ (BOOL)isColor:(UIColor* )color1 similarWith:(UIColor* )color2 {
    NSInteger rgb1 = [self rgbFromColor:color1];

    NSInteger rgb2 = [self rgbFromColor:color2];
    
    return labs(rgb1-rgb2) < 5;
}

+ (void)gradientColors:(NSArray *)colors onView:(UIView *)view horizontal:(BOOL)isHorizontal
{
    NSMutableArray *cgColors = [NSMutableArray arrayWithCapacity:4];
    [colors enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        [cgColors addObject:(id)[(UIColor *)obj CGColor]];
    }];
    CAGradientLayer *gradient = [CAGradientLayer layer];
    if (isHorizontal)
    {
        gradient.startPoint = CGPointMake(0, 0.5);
        gradient.endPoint = CGPointMake(1, 0.5);
    }
    else
    {
        gradient.startPoint = CGPointMake(0.5, 0);
        gradient.endPoint = CGPointMake(0.5, 1);
    }
    gradient.frame = view.bounds;
    gradient.colors = cgColors;
    [view.layer insertSublayer:gradient atIndex:0];
}

+ (NSUInteger)rgbOfPoint:(CGPoint)point onLayer:(CALayer *)layer
{
    unsigned char pixel[4] = {0};
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(pixel, 1, 1, 8, 4, colorSpace, kCGImageAlphaPremultipliedLast);
    
    CGContextTranslateCTM(context, -point.x, -point.y);
    
    [layer renderInContext:context];
    
    CGContextRelease(context);
    CGColorSpaceRelease(colorSpace);
    
    //NSLog(@"pixel: %d %d %d %d", pixel[0], pixel[1], pixel[2], pixel[3]);
    
    NSUInteger rgba = [self rgbFromR:pixel[0] g:pixel[1] b:pixel[2]];
    
    rgba = (rgba << 8) + pixel[3];
    
    return rgba;
}


@end

// Retina设备上实际绘制了宽度1px的非常锐利的线
void draw1PxStroke(CGContextRef context, CGPoint startPoint, CGPoint endPoint, CGColorRef color)
{
    CGFloat lineWidth = 0.5;
    CGFloat offset = 0.25;
    CGContextSaveGState(context);
    CGContextSetLineCap(context, kCGLineCapSquare);
    CGContextSetStrokeColorWithColor(context, color);
    CGContextSetLineWidth(context, lineWidth);
    CGContextMoveToPoint(context, startPoint.x + offset, startPoint.y + offset);
    CGContextAddLineToPoint(context, endPoint.x + offset, endPoint.y + offset);
    CGContextStrokePath(context);
    CGContextRestoreGState(context);
}

void fillRectWithColor(CGContextRef context, CGRect rectToFill, CGColorRef color)
{
    CGContextSaveGState(context);
    CGContextSetFillColorWithColor(context, color);
    CGContextFillRect(context, rectToFill);
    CGContextRestoreGState(context);
}

@implementation HSColorScheme

+ (UIColor*)colorWithDarkMode:(UIColor*)darkColor lightColor:(UIColor*)lightColor{
    
    UIColor* color = nil;
    if(@available(iOS 13.0,*)){
        color = [UIColor colorWithDynamicProvider:^UIColor *_Nonnull(UITraitCollection *_Nonnull trait){
            if(trait.userInterfaceStyle == UIUserInterfaceStyleDark){
                return darkColor;
            }
            else{
                return lightColor;
            }
        }];
    }
    else{
        color = lightColor;
    }
    
    return color;
}

+ (UIColor*)colorWithDarkModeRGB:(NSUInteger)darkColor lightColor:(NSUInteger)lightColor{
    
    UIColor* color = nil;
    if(@available(iOS 13.0,*)){
        color = [UIColor colorWithDynamicProvider:^UIColor *_Nonnull(UITraitCollection *_Nonnull trait){
            if(trait.userInterfaceStyle == UIUserInterfaceStyleDark){
                return [HSColorUtils colorWithRGB:darkColor];
            }
            else{
                return [HSColorUtils colorWithRGB:lightColor];
            }
        }];
    }
    else{
        color = [HSColorUtils colorWithRGB:lightColor];
    }
    
    return color;
}

+ (UIColor*)colorForUserInterfaceStyle:(UIColor*)color userInterfaceStyle:(UIUserInterfaceStyle)userInterfaceStyle API_AVAILABLE(tvos(10.0)) API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(watchos){
    UITraitCollection* traitCollection = [UITraitCollection traitCollectionWithUserInterfaceStyle:userInterfaceStyle];
    return [color resolvedColorWithTraitCollection:traitCollection];
}

+ (UIColor*)colorGreenLight{
    
    return [self colorWithDarkMode:[[HSColorUtils colorWithRGB:0x23a4a9] colorWithAlphaComponent:0.3] lightColor:[[HSColorUtils colorWithRGB:0x32bac0] colorWithAlphaComponent:0.3]];
}

+ (UIColor*)colorGreenNormal{
    
    return [self colorWithDarkModeRGB:0x23a4a9 lightColor:0x32bac0];
}

+ (UIColor*)colorGreenHeavy{
    
    return [self colorWithDarkModeRGB:0x158b90 lightColor:0x25a9af];
}

// Aborting
+ (UIColor*)colorGreen{
    
    return [self colorWithDarkModeRGB:0x23a4a9 lightColor:0x32bac0];
}

+ (UIColor*)colorRedLight{
    
    return [self colorWithDarkMode:[[HSColorUtils colorWithRGB:0xd92719] colorWithAlphaComponent:0.3] lightColor:[[HSColorUtils colorWithRGB:0xf43f31] colorWithAlphaComponent:0.3]];
}

+ (UIColor*)colorRedNormal{
    
    return [self colorWithDarkModeRGB:0xd92719 lightColor:0xf43f31];
}

+ (UIColor*)colorRedHeavy{
    
    return [self colorWithDarkModeRGB:0xb62920 lightColor:0xd53c32];
}

+ (UIColor*)colorBlue{
    
    return [self colorWithDarkModeRGB:0x3774e5 lightColor:0x4b89ff];
}

+ (UIColor*)colorWhite{
    
    return [self colorWithDarkModeRGB:0x000000 lightColor:0xffffff];
}

+ (UIColor*)colorGrayLighter{
    
    return [self colorWithDarkModeRGB:0x262626 lightColor:0xe5e5e5];
}

+ (UIColor*)colorGrayLight{
    
    return [self colorWithDarkModeRGB:0x3a3a3c lightColor:0xcccccc];
}

+ (UIColor*)colorGrayNormal{
    
    return [self colorWithDarkModeRGB:0x666666 lightColor:0x999999];
}

+ (UIColor*)colorGrayAbnormal{
    
    return [self colorWithDarkModeRGB:0x7f7f7f lightColor:0x808080];
}

+ (UIColor*)colorGrayHeavy{
    
    return [self colorWithDarkModeRGB:0x999999 lightColor:0x666666];
}

+ (UIColor*)colorGrayHeavier{
    
    return [self colorWithDarkModeRGB:0xcccccc lightColor:0x333333];
}

+ (UIColor*)colorBlack{
    
    return [self colorWithDarkModeRGB:0xffffff lightColor:0x000000];
}

+ (UIColor*)colorForeground{
    
    return [self colorWithDarkModeRGB:0x1a1a1a lightColor:0xffffff];
}

+ (UIColor*)colorBackground{
    
    return [self colorWithDarkModeRGB:0x000000 lightColor:0xf7f7f7];
}

+ (UIColor*)colorBackgroundWhite{
    
    return [self colorWithDarkModeRGB:0x1a1a1a lightColor:0xffffff];
}

+ (UIColor*)colorOverlayerBlack{
    
    return [self colorWithDarkMode: [UIColor.blackColor colorWithAlphaComponent:0.7] lightColor:[UIColor.blackColor colorWithAlphaComponent:0.4]];
}

+ (UIColor*)colorline{
    
    return [self colorWithDarkModeRGB:0x262626 lightColor:0xe5e5e5];
}

+ (UIColor*)colorTextTitle{
    
    return [self colorWithDarkModeRGB:0xf2f2f2 lightColor:0x333333];
}

+ (UIColor*)colorSecondary{
    
    return [self colorWithDarkModeRGB:0xdd7c0c lightColor:0xfe8e0e];
}

@end
