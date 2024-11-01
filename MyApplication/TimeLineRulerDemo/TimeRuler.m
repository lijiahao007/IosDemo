//
//  TimeRuler.m
//  MyApplication
//
//  Created by HS on 2024/10/23.
//

#import "TimeRuler.h"
#import "TimeRulerLayer.h"

#define kIndicatorDefaultColor      ([UIColor blueColor])  //指示器默认颜色
#define kIndicatorDefaultLength     80  //指示器高度

@interface TimeRuler() <UIScrollViewDelegate, UIGestureRecognizerDelegate>
@property (nonatomic, assign) NSInteger currentTime;
@property (nonatomic, strong) TimeRulerLayer* rulerLayer;
@property (nonatomic, assign) CGFloat rulerWidth;
@property (nonatomic, assign) CGFloat oldRulerWidth;

@property (nonatomic, strong) UIScrollView* scrollView;

@property (nonatomic, strong) UIView* topLine;
@property (nonatomic, strong) UIView* btmLine;

@property (nonatomic, assign) CGFloat startScale;
@property (nonatomic, assign) BOOL isTouch;

@property (nonatomic, strong) UIImageView* indicatorView;
@property (nonatomic, strong) UIView* rulerBackgroundView;

@property (nonatomic, assign) double scaleTimestamp;
@property (nonatomic, assign) BOOL isScaleJustNow;

@property (nonatomic, strong) UIPinchGestureRecognizer* pinchGesture;

@end


@implementation TimeRuler

-(void) setSelectedRange:(NSArray<TimeRulerInfo*>*)rangeArray {
    _rulerLayer.selectedRange = rangeArray;
}

- (instancetype)initWithFrame:(CGRect)frame{
    self = [super initWithFrame:frame];
    if (self) {
        _rulerWidth = CGRectGetWidth(self.bounds) * 6.0;
        [self setupUI];
    }
    return self;
}

- (void) setupUI {
    [self setupLineUI];
    [self setupScrollViewUI];
    [self setupRulerLayer];
    [self setupIndicator];
    self.pinchGesture = [[UIPinchGestureRecognizer alloc]initWithTarget:self action:@selector(pinchAction:)];
    self.pinchGesture.delegate = self;
    self.pinchGesture.cancelsTouchesInView = NO;
    [self.scrollView addGestureRecognizer:self.pinchGesture];
    
    self.backgroundColor = UIColor.clearColor;
}

-(void) pinchAction:(UIPinchGestureRecognizer*)gesture {
    LLog(@"state:%lu", gesture.state);
    if (gesture.state == UIGestureRecognizerStateBegan) {
        _startScale = gesture.scale;
    } else if (gesture.state == UIGestureRecognizerStateChanged) {
        [self updateFrame:gesture.scale/_startScale];
        _startScale = gesture.scale;
    } else if (gesture.state == UIGestureRecognizerStateEnded) {
        _scrollView.scrollEnabled = YES;
    }
    
    if (gesture.numberOfTouches < 2) {
        [gesture setState:UIGestureRecognizerStateEnded];
    }
}

-(void) updateFrame:(CGFloat)scale {
    CGFloat updateRulerWidth = _rulerLayer.bounds.size.width * scale;
    CGFloat rulerMinWidth = [self getMinRulerWidth];

    if (updateRulerWidth < rulerMinWidth){
        updateRulerWidth = rulerMinWidth;
    }
    
    if (updateRulerWidth > TimeRulerLayer.rulerMaxWidth) {
        updateRulerWidth = TimeRulerLayer.rulerMaxWidth;
    }
    
    _oldRulerWidth = _rulerWidth;
    _rulerWidth = updateRulerWidth;
    
    [self setNeedsLayout];
}

-(void) setupLineUI {
    _topLine = [[UIView alloc]init];
    _btmLine = [[UIView alloc]init];
    _topLine.backgroundColor = /*[[UIColor alloc]initWithWhite:0.78 alpha:1.0]*/ [UIColor clearColor];
    _btmLine.backgroundColor = /*[[UIColor alloc]initWithWhite:0.78 alpha:1.0]*/ [UIColor clearColor];
    [self addSubview:_topLine];
    [self addSubview:_btmLine];
}

-(void) setupScrollViewUI {
    _scrollView = [[UIScrollView alloc]initWithFrame:self.bounds];
    _scrollView.delegate = self;
    [_scrollView.pinchGestureRecognizer setEnabled:NO];
    [_scrollView setShowsHorizontalScrollIndicator:NO];
    [_scrollView setContentInsetAdjustmentBehavior:UIScrollViewContentInsetAdjustmentNever];
    [self addSubview:_scrollView];
}

-(void) setupRulerLayer {
    _rulerLayer = [[TimeRulerLayer alloc]init];
    [self updateRulerStyle];
    [_scrollView.layer addSublayer:_rulerLayer];
}

- (void)setStyle:(TimeRulerStyle)style {
    _style = style;
    [self updateRulerStyle];
}

- (void)setFrame:(CGRect)frame {
    [super setFrame:frame];
    [_rulerLayer setNeedsDisplay];
}

-(void) updateRulerStyle {
    if (_style == TimeRulerStyleDefault) {
        _rulerLayer.showTopMark = YES;
        _rulerLayer.showBottomMark = NO;
        _rulerLayer.textPosition = TimeRulerLayer_TextTop;
    } else {
        _rulerLayer.showTopMark = YES;
        _rulerLayer.showBottomMark = YES;
        _rulerLayer.textPosition = TimeRulerLayer_TextCenter;
    }
    [self.rulerLayer setNeedsDisplay];
}

-(void) setupIndicator {
    _indicatorView = [[UIImageView alloc] init];
    [self updateIndicatorFrame];
    [self addSubview:_indicatorView];
}

- (void) updateIndicatorFrame {
    CGSize size = self.bounds.size;
    if(self.style == TimeRulerStyleDefault) {
        //modify by 547

        
        NSDictionary *strAttributes = @{NSFontAttributeName: [UIFont systemFontOfSize:kScaleDefaultFontSize]};;
        NSString *str = [self timeFormatted:0];
        CGRect strRect = [str boundingRectWithSize:CGSizeMake(MAXFLOAT, MAXFLOAT)
                                           options:NSStringDrawingUsesLineFragmentOrigin
                                        attributes:strAttributes
                                           context:nil];
        
        CGFloat indicatorLength = self.bounds.size.height - strRect.size.height - 4;
        CGFloat indicatorWidth = 2.0;
        
        _indicatorView.frame = CGRectMake(size.width * 0.5 - indicatorWidth/ 2.0, strRect.size.height + 4, indicatorWidth, indicatorLength);
        _indicatorView.layer.cornerRadius = 2;
        [_indicatorView setImage:nil];
        _indicatorView.backgroundColor = HSColorScheme.colorBlue;
        _rulerBackgroundView.hidden = YES;
        //end by 547
    }
    else {
        CGFloat indicatorWidth = 8.0;
        CGFloat indicatorHeight =  self.bounds.size.height;

        _indicatorView.frame = CGRectMake(size.width * 0.5 - indicatorWidth/2, 0, indicatorWidth, indicatorHeight);
        [_indicatorView setImage:[UIImage imageNamed:@"icon_sjz_axis"]];
        _indicatorView.backgroundColor = UIColor.clearColor;
        _rulerBackgroundView.hidden = YES;
    }
}



- (NSString *)timeFormatted:(int)totalSeconds{
    
    //int seconds = totalSeconds % 60;
    int minutes = (totalSeconds / 60) % 60;
    int hours = totalSeconds / 3600;
    
    return [NSString stringWithFormat:@"%02d:%02d",hours, minutes];
    
}

-(CGFloat) getMinRulerWidth {
    return (CGRectGetWidth(self.bounds) + 2 * TimeRulerLayer.sideOffset);
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    CGFloat sideInset = CGRectGetWidth(self.bounds) / 2.0;
    
    _scrollView.frame = self.bounds;
    _scrollView.contentInset = UIEdgeInsetsMake(0, sideInset - TimeRulerLayer.sideOffset, 0, sideInset - TimeRulerLayer.sideOffset);
        
    if (_rulerWidth < [self getMinRulerWidth]) {
        // 横竖屏切换时，bounds宽度会变化。
        _rulerWidth = [self getMinRulerWidth];
    }
    
    [CATransaction begin];
    [CATransaction setDisableActions:YES];
//    NSLog(@"TimeRuler layoutSubviews _rulerWidth:%f height:%f _currentTime:%d", _rulerWidth, CGRectGetHeight(self.bounds), _currentTime);
    _rulerLayer.frame = CGRectMake(0, 0, _rulerWidth, CGRectGetHeight(self.bounds));
    [CATransaction commit];
    
    _scrollView.contentSize = CGSizeMake(_rulerWidth, CGRectGetHeight(self.bounds));
    
    _topLine.frame = CGRectMake(0, 0, CGRectGetWidth(self.bounds), 1.0);
    _btmLine.frame = CGRectMake(0, CGRectGetHeight(self.bounds) - 1.0, CGRectGetWidth(self.bounds), 1.0);
    
    // 保证缩放过程中心保持不变
    _scrollView.contentOffset = [self contentOffset:_currentTime];
    NSLog(@"TimeRuler layoutSubviews");
    _scaleTimestamp = CFAbsoluteTimeGetCurrent();
    _isScaleJustNow = YES;
    [self updateIndicatorFrame];
}

-(CGPoint) contentOffset:(NSInteger)current {
    CGFloat proportion = current / (24 * 3600.0);
    CGFloat proportionWidth = (_scrollView.contentSize.width - TimeRulerLayer.sideOffset * 2) * proportion;
    return CGPointMake(proportionWidth - _scrollView.contentInset.left, _scrollView.contentOffset.y);
}

#pragma mark UIScrollViewDelegate
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView {
    _isTouch = YES;
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView {
    if (_isScaleJustNow) {
        // layoutSubviews 中的contentOffset设置会触发scrollViewDidScroll。
        // 缩放过程中，不做滚动处理。（避免浮点型误差导致的中心移动）
        double dis = CFAbsoluteTimeGetCurrent() - _scaleTimestamp;
        _isScaleJustNow = NO;
        NSLog(@"scrollViewDidScroll dis:%f", dis);
        if (dis < 0.1) {
            return;
        }
    }
    
    if (scrollView.panGestureRecognizer.numberOfTouches == 2) {
        // 两个手指接触时，事件响应移交到pinchGesture。
        scrollView.scrollEnabled = NO;
        [self.pinchGesture setState:UIGestureRecognizerStateBegan];
        return;
    } else {
        scrollView.scrollEnabled = YES;
    }
    
    CGFloat proportionWidth = scrollView.contentOffset.x + scrollView.contentInset.left;
    CGFloat proportion = proportionWidth / (scrollView.contentSize.width - TimeRulerLayer.sideOffset * 2);
    int64_t value = (int64_t)ceil(proportion * 24 * 3600);
    NSLog(@"scrollViewDidScroll value:%lld %f  proportionWidth:%f, proportion:%f", value, ceil(proportion * 24 * 3600), proportionWidth, proportion);
    
    if (value >= 0) {
        _currentTime = value;
    }
   
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView {
    _isTouch = NO;
}

- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate {
    if (!decelerate) {
        _isTouch = NO;
    }
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer {
    return YES;
}

@end
