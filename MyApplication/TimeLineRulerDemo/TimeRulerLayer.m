//
//  TimeRulerLayer.m
//  MyApplication
//
//  Created by HS on 2024/10/23.
//  Rewrite from https://github.com/qianquanQutman/TimeRuler
//

#import "TimeRulerLayer.h"
#import "TimeRulerMark.h"
#import "TimeRulerInfo.h"

@interface TimeRulerLayer()
@property (nonatomic, strong) TimeRulerMark* minorMark;
@property (nonatomic, strong) TimeRulerMark* middleMark;
@property (nonatomic, strong) TimeRulerMark* majorMark;

@end

@implementation TimeRulerLayer

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.backgroundColor = [UIColor clearColor].CGColor;
    }
    return self;
}

+ (CGFloat)sideOffset {
    return 30.0;
}
+ (CGFloat)rulerMaxWidth {
    return 10800.0;
}

- (void)setSelectedRange:(NSArray<TimeRulerInfo *> *)selectedRange {
    _selectedRange = selectedRange;
    [self setNeedsDisplay];
}

- (void)setFrame:(CGRect)frame {
    [super setFrame:frame];
    [self setNeedsDisplay];
}

- (void)display {
    [CATransaction begin];
    [CATransaction setDisableActions:YES];
    [self drawToImage];
    [CATransaction commit];
}

- (void) drawToImage {
    RulerMarkFrequency frequency = RulerMarkFrequency_Minute_10;
    
    // 每小时占用的宽度
    CGFloat hourWidth = (CGRectGetWidth(self.bounds) - TimeRulerLayer.sideOffset * 2) / 24.0;
    
    // 根据宽度来判断显示标记的级别
    if (hourWidth / 30.0 >= 8.0) {
        frequency = RulerMarkFrequency_Minute_2;
    } else if (hourWidth / 6.0 >= 5.0) {
        frequency = RulerMarkFrequency_Minute_10;
    } else {
        frequency = RulerMarkFrequency_Hour;
    }
    
    // 计算有多少个标记
    int numberOfLine = 24 * 3600 / frequency;
    CGFloat lineOffset = (CGRectGetWidth(self.bounds) - TimeRulerLayer.sideOffset * 2) / (CGFloat)numberOfLine;
    
    UIGraphicsBeginImageContextWithOptions(self.bounds.size, false, [UIScreen mainScreen].scale);
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    NSDictionary *attrsDictionary = [NSDictionary dictionaryWithObject:[UIFont systemFontOfSize:11] forKey:NSFontAttributeName];
    NSAttributedString* attributeString = [[NSAttributedString alloc]initWithString:@"00:00" attributes:attrsDictionary];
    
    // 计算文字最宽宽度
    CGFloat hourTextWidth = attributeString.size.width;
    
    // 绘制选中区域
    if (_selectedRange && ctx) {
        CGContextSetFillColorWithColor(ctx, [HSColorScheme colorBlue].CGColor);
        
        for (TimeRulerInfo* info in _selectedRange) {
            int startSecond = info.startSecond;
            int endSecond = info.endSecond;
            
            CGFloat x = (((CGFloat)startSecond) / (24*3600.0)) * (CGRectGetWidth(self.bounds) - TimeRulerLayer.sideOffset * 2) + TimeRulerLayer.sideOffset;
            CGFloat width = ((CGFloat)(endSecond - startSecond)) / (24 * 3600.0) * (CGRectGetWidth(self.bounds) - TimeRulerLayer.sideOffset * 2);
            CGRect rect = CGRectMake(x, 0, width, CGRectGetHeight(self.bounds));
            CGContextFillRect(ctx, rect);
        }
    }
    
    for (int i = 0; i <= numberOfLine; i++) {
        // 计算每个标记的属性
        CGFloat position = i * lineOffset;
        int timeSecond = i * frequency;
        BOOL showText = NO;
        NSString* timeString = @"00:00";
        TimeRulerMark* mark = self.minorMark;
        
        if (timeSecond % 3600 == 0) { // 小时标尺
            mark = self.majorMark;
            if (hourWidth > hourTextWidth + 5.0) {
                // 每小时都能画时间
                showText = YES;
            } else if ((hourWidth * 3) > (hourTextWidth + 5) * 2) {
                // 每两个小时画一个时间
                showText = timeSecond % (3600 * 2) == 0;
            } else {
                // 每四小时画一个时间
                showText = timeSecond % (3600 * 4) == 0;
            }
        } else if (timeSecond % 600 == 0) {
            // 每10中的标识
            mark = self.middleMark;
            showText = frequency == RulerMarkFrequency_Minute_2;
        }
        
        int hour = timeSecond / 3600;
        int min = timeSecond % 3600 / 60;
        timeString = [NSString stringWithFormat:@"%02d:%02d", hour, min];
        
        [self drawMarkIn:ctx position:position timeString:timeString mark:mark showText:showText];
    }
    
    
    UIImage* imageToDraw = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    self.contents = (__bridge id _Nullable)(imageToDraw.CGImage);
    
//    NSLog(@"TimeRulerLayer drawToImage numberOfLine:%d imageToDraw:%@", numberOfLine, imageToDraw);
}

-(void) drawMarkIn:(CGContextRef)context position:(CGFloat)position timeString:(NSString*)timeString mark:(TimeRulerMark*)mark showText:(BOOL)showText {
    NSDictionary *textAttribute = @{
        NSFontAttributeName: mark.font,
        NSForegroundColorAttributeName: mark.textColor
    };
    NSAttributedString* attributeString = [[NSAttributedString alloc]initWithString:timeString attributes:textAttribute];
    CGSize textSize = attributeString.size;
    CGFloat rectX = position + TimeRulerLayer.sideOffset - mark.size.width * 0.5;
    CGFloat rectY = 0;
    // 上标记rect
    CGRect rect = CGRectMake(rectX, rectY, mark.size.width, mark.size.height);
    // 下标记rect
    CGRect btmRect = CGRectMake(rectX, CGRectGetHeight(self.bounds) - mark.size.height, mark.size.width, mark.size.height);
    CGContextSetFillColorWithColor(context, mark.color.CGColor);
    CGContextFillRect(context, rect);
    CGContextFillRect(context, btmRect);
    if (showText) {
        // 绘制时间文字
        CGFloat textRectX = position + TimeRulerLayer.sideOffset - textSize.width * 0.5;
        CGFloat textRectY = CGRectGetMaxY(rect) + 4.0;
        if ((textRectY + textSize.height * 0.5) > (CGRectGetHeight(self.bounds) * 0.5)) {
            textRectY = (CGRectGetHeight(self.bounds) - textSize.height) * 0.5;
        }
        CGRect textRect = CGRectMake(textRectX, textRectY, textSize.width, textSize.height);
        [timeString drawInRect:textRect withAttributes:textAttribute];
    }
}

#pragma mark - lazy loading
- (TimeRulerMark *)minorMark {
    if (_minorMark) return _minorMark;
    
    _minorMark = [[TimeRulerMark alloc]init];
    _minorMark.frequency = RulerMarkFrequency_Minute_2;
    _minorMark.size = CGSizeMake(1.0, 4.0);
    return _minorMark;
}

- (TimeRulerMark *)middleMark {
    if (_middleMark) return _middleMark;
    
    _middleMark = [[TimeRulerMark alloc]init];
    _middleMark.frequency = RulerMarkFrequency_Minute_10;
    _middleMark.size = CGSizeMake(1.0, 8.0);
    return _middleMark;
}

- (TimeRulerMark *)majorMark {
    if (_majorMark) return _majorMark;
    
    _majorMark = [[TimeRulerMark alloc]init];
    _majorMark.frequency = RulerMarkFrequency_Hour;
    _majorMark.size = CGSizeMake(1.0, 13.0);
    return _majorMark;
}

@end
