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

#define kMajorScaleDefaultLength    20.0  //主刻度高度
#define kMiddleScaleDefaultLength   15.0  //中间刻度高度
#define kMinorScaleDefaultLength    10.0  //小刻度高度
#define kRulerDefaultBackgroundColor    ([UIColor clearColor])  //刻度尺背景颜色
#define kScaleDefaultColor          ([UIColor lightGrayColor])  //刻度颜色
#define kScaleDefaultFontColor      ([UIColor colorWithHex:0x666666])  //刻度字体颜色
#define kTextMarkDistance           4.0 // 刻度和文字的间距

@interface TimeRulerLayer()
@property (nonatomic, strong) TimeRulerMark* minorMark;
@property (nonatomic, strong) TimeRulerMark* middleMark;
@property (nonatomic, strong) TimeRulerMark* majorMark;
@property (nonatomic, strong) NSMutableArray<CALayer*>* rangeShapeArr;

@end

@implementation TimeRulerLayer

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.backgroundColor = kRulerDefaultBackgroundColor.CGColor;
        _showTopMark = YES;
        _showBottomMark = YES;
    }
    return self;
}

+ (CGFloat)sideOffset {
    return 30.0;
}
+ (CGFloat)rulerMaxWidth {
    return 1000 * 24.0;
}

- (void)setSelectedRange:(NSArray<TimeRulerInfo *> *)selectedRange {
    NSLog(@"TimeRulerLayer setSelectedRange");
    
    // 1. KVO 通知
    [self willChangeValueForKey:@"selectedRange"];
    
    // 2. 安全检查
    if (![selectedRange isKindOfClass:[NSArray class]]) {
        _selectedRange = nil;
        return;
    }
    
    // 3. 执行 copy
    _selectedRange = [self sortByPriority:selectedRange];
    [self initShadeLayer];
    
    // 4. KVO 通知
    [self didChangeValueForKey:@"items"];
    
    [self setNeedsDisplay];
}

-(void) initShadeLayer {
    for (CAShapeLayer* layer in self.rangeShapeArr) {
        [layer removeFromSuperlayer];
    }
    [self.rangeShapeArr removeAllObjects];

    for (TimeRulerInfo* info in _selectedRange) {
        CALayer* shapeLayer = [[CAShapeLayer alloc]init];
        
        shapeLayer.backgroundColor = [info.color colorWithAlphaComponent:0.8].CGColor;
        
        [self.rangeShapeArr addObject:shapeLayer];
        [self addSublayer:shapeLayer];
    }
}

/**
 按照优先级倒序排序
 */
-(NSArray<TimeRulerInfo*>*) sortByPriority:(NSArray<TimeRulerInfo*>*)targetArr {
    NSArray* res = nil;
    if (targetArr) {
        res = [targetArr sortedArrayUsingComparator:^NSComparisonResult(TimeRulerInfo*  _Nonnull obj1, TimeRulerInfo*  _Nonnull obj2) {
            if (obj1.priority < obj2.priority) {
                return NSOrderedAscending;
            } else if (obj1.priority > obj2.priority) {
                return NSOrderedDescending;
            } else {
                return NSOrderedSame;
            }
        }];
    }
    return res;
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
    if (hourWidth / 60.0 >= 4.0) { // hourWidth >= 180.0
        frequency = RulerMarkFrequency_Minute_1;
    } else if (hourWidth / 6.0 >= 5.0) { // hourWidth >= 30.0
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
    double total = 0;

    if (_selectedRange) {
        
        NSDictionary *textAttribute = @{
            NSFontAttributeName: self.majorMark.font,
        };
        
        NSAttributedString* attributeString = [[NSAttributedString alloc]initWithString:@"00:00" attributes:textAttribute];
        CGSize textSize = attributeString.size;
        
        int index = 0;
        
        
        for (TimeRulerInfo* info in _selectedRange) {

            int startSecond = info.startSecond;
            int endSecond = info.endSecond;

            // 使用CALayer绘制矩形块，会不直接在Image那里绘制要快一点。特别是Image特别长的时候。
            CGFloat x = (((CGFloat)startSecond) / (24*3600.0)) * (CGRectGetWidth(self.bounds) - TimeRulerLayer.sideOffset * 2) + TimeRulerLayer.sideOffset;
            CGFloat y = textSize.height + kTextMarkDistance + self.majorMark.size.height;
            CGFloat width = ((CGFloat)(endSecond - startSecond)) / (24 * 3600.0) * (CGRectGetWidth(self.bounds) - TimeRulerLayer.sideOffset * 2);
            CGFloat height = CGRectGetHeight(self.bounds) - y;
            CGRect frame = CGRectMake(x, y, width, height);

            self.rangeShapeArr[index].frame = frame;
            index++;
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
            showText = frequency == RulerMarkFrequency_Minute_1;
        }
        
        int hour = timeSecond / 3600;
        int min = timeSecond % 3600 / 60;
        timeString = [NSString stringWithFormat:@"%02d:%02d", hour, min];
        
        [self drawMarkIn:ctx position:position timeString:timeString mark:mark showText:showText];
    }
    
    UIImage* imageToDraw = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    self.contents = (__bridge id _Nullable)(imageToDraw.CGImage);
}

-(void) drawMarkIn:(CGContextRef)context position:(CGFloat)position timeString:(NSString*)timeString mark:(TimeRulerMark*)mark showText:(BOOL)showText {
    NSDictionary *textAttribute = @{
        NSFontAttributeName: mark.font,
        NSForegroundColorAttributeName: mark.textColor
    };
    NSAttributedString* attributeString = [[NSAttributedString alloc]initWithString:timeString attributes:textAttribute];
    CGSize textSize = attributeString.size;
    
    if (showText) {
        // 绘制时间文字
        CGFloat textRectX = position + TimeRulerLayer.sideOffset - textSize.width * 0.5;
        CGFloat textRectY = 0;
        CGRect textRect = CGRectMake(textRectX, textRectY, textSize.width, textSize.height);
        [timeString drawInRect:textRect withAttributes:textAttribute];
    }
    
    CGFloat rectX = position + TimeRulerLayer.sideOffset - mark.size.width * 0.5;
    CGFloat rectY = textSize.height + kTextMarkDistance;
    // 上标记rect
    CGRect rect = CGRectMake(rectX, rectY, mark.size.width, mark.size.height);
    // 下标记rect
    CGRect btmRect = CGRectMake(rectX, CGRectGetHeight(self.bounds) - mark.size.height, mark.size.width, mark.size.height);
    CGContextSetFillColorWithColor(context, mark.color.CGColor);
    if (_showTopMark) {
        CGContextFillRect(context, rect);
    }
    if (_showBottomMark) {
        CGContextFillRect(context, btmRect);
    }
}

#pragma mark - lazy loading
- (TimeRulerMark *)minorMark {
    if (_minorMark) return _minorMark;
    
    _minorMark = [[TimeRulerMark alloc]init];
    _minorMark.frequency = RulerMarkFrequency_Minute_1;
    _minorMark.size = CGSizeMake(1.0, kMinorScaleDefaultLength);
    _minorMark.color = kScaleDefaultColor;
    _minorMark.font = [UIFont systemFontOfSize:kScaleDefaultFontSize];
    return _minorMark;
}

- (TimeRulerMark *)middleMark {
    if (_middleMark) return _middleMark;
    
    _middleMark = [[TimeRulerMark alloc]init];
    _middleMark.frequency = RulerMarkFrequency_Minute_10;
    _middleMark.size = CGSizeMake(1.0, kMiddleScaleDefaultLength);
    _middleMark.color = kScaleDefaultColor;
    _middleMark.font = [UIFont systemFontOfSize:kScaleDefaultFontSize];
    return _middleMark;
}

- (TimeRulerMark *)majorMark {
    if (_majorMark) return _majorMark;
    
    _majorMark = [[TimeRulerMark alloc]init];
    _majorMark.frequency = RulerMarkFrequency_Hour;
    _majorMark.size = CGSizeMake(1.0, kMajorScaleDefaultLength);
    _majorMark.color = kScaleDefaultColor;
    _majorMark.font = [UIFont systemFontOfSize:kScaleDefaultFontSize];
    return _majorMark;
}

- (NSMutableArray<CALayer *> *)rangeShapeArr {
    if (_rangeShapeArr != nil) return _rangeShapeArr;
    _rangeShapeArr = [NSMutableArray array];
    return _rangeShapeArr;
}
@end