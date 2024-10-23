//
//  TimelineView.m
//  MyApplication
//
//  Created by HS on 2024/10/23.
//

#import "TimelineView.h"

@interface TimelineView ()

@property (nonatomic, strong) NSDate *currentTime;
@property (nonatomic, assign) BOOL isDragging;
@property (nonatomic, strong) UIView *indicatorView;
@property (nonatomic, strong) UILabel *currentTimeLabel;
@property (nonatomic, strong) CADisplayLink *displayLink;

// 缩放相关属性
@property (nonatomic, assign) CGFloat baseScale;        // 基准缩放比例
@property (nonatomic, assign) CGFloat currentZoomScale;  // 当前缩放比例
@property (nonatomic, assign) CGFloat minTimeScale;     // 最小时间刻度（秒）
@property (nonatomic, assign) CGFloat maxTimeScale;     // 最大时间刻度（秒）
@property (nonatomic, assign) CGFloat pixelsPerSecond;  // 每秒对应的像素数

// UI配置
@property (nonatomic, assign) CGFloat tickWidth;
@property (nonatomic, assign) CGFloat indicatorWidth;

@end

@implementation TimelineView

#pragma mark - Initialization

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self commonInit];
    }
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)coder {
    self = [super initWithCoder:coder];
    if (self) {
        [self commonInit];
    }
    return self;
}

- (void)commonInit {
    // 初始化默认值
    _currentTime = [NSDate date];
    _timelineHeight = 60.0;
    _majorTickHeight = 20.0;
    _minorTickHeight = 10.0;
    _tickWidth = 1.0;
    _indicatorWidth = 2.0;
    _indicatorColor = [UIColor redColor];
    
    // 初始化缩放相关属性
    _baseScale = 60.0;                   // 基准比例：1分钟
    _currentZoomScale = 60.0;            // 初始显示1分钟
    _minTimeScale = 10.0;                // 最小显示10秒
    _maxTimeScale = 43200.0;             // 最大显示12小时
    _pixelsPerSecond = self.frame.size.width / _currentZoomScale;
    
    // 初始化时间格式器
    _timeFormatter = [[NSDateFormatter alloc] init];
    _timeFormatter.dateFormat = @"HH:mm:ss";
    
    [self setupViews];
    [self setupGestures];
    [self startTimelineAnimation];
}

#pragma mark - Setup Methods

- (void)setupViews {
    // 创建时间指示器
    self.indicatorView = [[UIView alloc] init];
    self.indicatorView.backgroundColor = self.indicatorColor;
    [self addSubview:self.indicatorView];
    
    // 创建时间标签
    self.currentTimeLabel = [[UILabel alloc] init];
    self.currentTimeLabel.font = [UIFont systemFontOfSize:12];
    self.currentTimeLabel.textColor = self.indicatorColor;
    self.currentTimeLabel.textAlignment = NSTextAlignmentCenter;
    [self addSubview:self.currentTimeLabel];
    
    [self layoutIndicator];
}

- (void)setupGestures {
    UIPinchGestureRecognizer *pinchGesture = [[UIPinchGestureRecognizer alloc]
                                              initWithTarget:self action:@selector(handlePinch:)];
    [self addGestureRecognizer:pinchGesture];
    
    UIPanGestureRecognizer *panGesture = [[UIPanGestureRecognizer alloc]
                                          initWithTarget:self action:@selector(handlePan:)];
    [self addGestureRecognizer:panGesture];
}

#pragma mark - Gesture Handlers

- (void)handlePinch:(UIPinchGestureRecognizer *)gesture {
    static CGFloat initialScale = 0;
    
    switch (gesture.state) {
        case UIGestureRecognizerStateBegan:
            initialScale = self.currentZoomScale;
            break;
            
        case UIGestureRecognizerStateChanged: {
            // 计算新的缩放比例
            CGFloat newScale = initialScale / gesture.scale;
            
            // 限制缩放范围
            newScale = MIN(MAX(newScale, self.minTimeScale), self.maxTimeScale);
            
            // 更新当前缩放比例
            self.currentZoomScale = newScale;
            
            // 更新每秒像素比
            self.pixelsPerSecond = self.frame.size.width / self.currentZoomScale;
            
            [self setNeedsDisplay];
            break;
        }
            
        case UIGestureRecognizerStateEnded:
            // 缩放结束后的处理
            [self adjustScaleAfterPinch];
            break;
            
        default:
            break;
    }
}

- (void)adjustScaleAfterPinch {
    // 可以根据当前比例调整到最接近的合适刻度
    NSArray *standardScales = @[@10, @30, @60, @300, @600, @1800, @3600, @7200, @14400, @43200];
    
    CGFloat closestScale = [standardScales.firstObject floatValue];
    CGFloat minDiff = fabs(self.currentZoomScale - closestScale);
    
    for (NSNumber *scale in standardScales) {
        CGFloat diff = fabs(self.currentZoomScale - scale.floatValue);
        if (diff < minDiff) {
            minDiff = diff;
            closestScale = scale.floatValue;
        }
    }
    
    // 使用动画过渡到标准刻度
    [UIView animateWithDuration:0.3 animations:^{
        self.currentZoomScale = closestScale;
        self.pixelsPerSecond = self.frame.size.width / self.currentZoomScale;
        [self setNeedsDisplay];
    }];
}

- (void)handlePan:(UIPanGestureRecognizer *)gesture {
    switch (gesture.state) {
        case UIGestureRecognizerStateBegan:
            self.isDragging = YES;
            break;
            
        case UIGestureRecognizerStateChanged: {
            CGPoint translation = [gesture translationInView:self];
            NSTimeInterval timeOffset = translation.x / self.pixelsPerSecond;
            self.currentTime = [self.currentTime dateByAddingTimeInterval:-timeOffset];
            [gesture setTranslation:CGPointZero inView:self];
            [self setNeedsDisplay];
            break;
        }
            
        case UIGestureRecognizerStateEnded:
        case UIGestureRecognizerStateCancelled: {
            self.isDragging = NO;
            CGPoint velocity = [gesture velocityInView:self];
            
            // 计算减速动画
            CGFloat decelerationTime = 0.5;
            CGFloat timeOffset = (velocity.x * decelerationTime) / self.pixelsPerSecond;
            
            [UIView animateWithDuration:decelerationTime
                                  delay:0
                                options:UIViewAnimationOptionCurveEaseOut
                             animations:^{
                self.currentTime = [self.currentTime dateByAddingTimeInterval:-timeOffset];
                [self setNeedsDisplay];
            } completion:nil];
            break;
        }
            
        default:
            break;
    }
}

#pragma mark - Drawing

- (void)drawRect:(CGRect)rect {
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    // 绘制背景
    CGContextSetFillColorWithColor(context, [UIColor whiteColor].CGColor);
    CGContextFillRect(context, rect);
    
    // 计算显示范围
    NSTimeInterval visibleDuration = self.currentZoomScale;
    NSDate *startTime = [self.currentTime dateByAddingTimeInterval:-visibleDuration / 2.0];
    
    // 确定刻度间隔
    NSTimeInterval majorTickInterval = [self getMajorTickIntervalForScale:self.currentZoomScale];
    NSInteger minorTickCount = 5;
    NSTimeInterval minorTickInterval = majorTickInterval / minorTickCount;
    
    // 绘制刻度线和标签
    NSInteger tickCount = ceil(visibleDuration / minorTickInterval);
    for (NSInteger i = 0; i <= tickCount; i++) {
        NSDate *tickTime = [startTime dateByAddingTimeInterval:i * minorTickInterval];
        CGFloat x = [self xPositionForDate:tickTime];
        
        if (i % minorTickCount == 0) {
            // 绘制主刻度
            [self drawTickAtX:x height:self.majorTickHeight inContext:context];
            [self drawTimeLabelForDate:tickTime atX:x];
        } else {
            // 绘制次刻度
            [self drawTickAtX:x height:self.minorTickHeight inContext:context];
        }
    }
    
    [self layoutIndicator];
}

- (NSTimeInterval)getMajorTickIntervalForScale:(CGFloat)scale {
    if (scale <= 60) {         // ≤1分钟
        return 10;              // 10秒一个主刻度
    } else if (scale <= 300) {  // ≤5分钟
        return 60;              // 1分钟一个主刻度
    } else if (scale <= 3600) { // ≤1小时
        return 300;             // 5分钟一个主刻度
    } else {
        return 3600;            // 1小时一个主刻度
    }
}

- (CGFloat)xPositionForDate:(NSDate *)date {
    NSTimeInterval offset = [date timeIntervalSinceDate:self.currentTime];
    return CGRectGetWidth(self.bounds) / 2.0 + offset * self.pixelsPerSecond;
}

- (void)drawTickAtX:(CGFloat)x height:(CGFloat)height inContext:(CGContextRef)context {
    CGContextSetStrokeColorWithColor(context, [UIColor blackColor].CGColor);
    CGContextSetLineWidth(context, self.tickWidth);
    CGContextMoveToPoint(context, x, CGRectGetHeight(self.bounds) - self.timelineHeight);
    CGContextAddLineToPoint(context, x, CGRectGetHeight(self.bounds) - self.timelineHeight + height);
    CGContextStrokePath(context);
}

- (void)drawTimeLabelForDate:(NSDate *)date atX:(CGFloat)x {
    NSString *timeString = [self.timeFormatter stringFromDate:date];
    NSDictionary *attributes = @{
        NSFontAttributeName: [UIFont systemFontOfSize:10],
        NSForegroundColorAttributeName: [UIColor blackColor]
    };
    
    CGSize size = [timeString sizeWithAttributes:attributes];
    CGRect rect = CGRectMake(x - size.width/2,
                             CGRectGetHeight(self.bounds) - self.timelineHeight + self.majorTickHeight + 2,
                             size.width,
                             size.height);
    
    [timeString drawInRect:rect withAttributes:attributes];
}

#pragma mark - Layout

- (void)layoutIndicator {
    CGFloat centerX = CGRectGetWidth(self.bounds) / 2;
    
    self.indicatorView.frame = CGRectMake(centerX - self.indicatorWidth/2,
                                          CGRectGetHeight(self.bounds) - self.timelineHeight,
                                          self.indicatorWidth,
                                          self.timelineHeight);
    
    self.currentTimeLabel.frame = CGRectMake(centerX - 50,
                                             CGRectGetHeight(self.bounds) - self.timelineHeight - 25,
                                             100,
                                             20);
    self.currentTimeLabel.text = [self.timeFormatter stringFromDate:self.currentTime];
}

#pragma mark - Timeline Updates

- (void)startTimelineAnimation {
    self.displayLink = [CADisplayLink displayLinkWithTarget:self
                                                   selector:@selector(updateTimeline)];
    [self.displayLink addToRunLoop:[NSRunLoop mainRunLoop]
                           forMode:NSRunLoopCommonModes];
}

- (void)updateTimeline {
    if (!self.isDragging) {
        self.currentTime = [NSDate date];
        [self setNeedsDisplay];
    }
}

#pragma mark - Cleanup

- (void)dealloc {
    [self.displayLink invalidate];
}


@end
