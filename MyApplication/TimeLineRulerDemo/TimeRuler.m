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

@interface TimeRuler() <UIScrollViewDelegate>
@property (nonatomic, assign) int currentTime;
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
@property (nonatomic, assign) CGFloat indicatorLength;

@property (nonatomic, assign) double scaleTimestamp;
@property (nonatomic, assign) BOOL isScaleJustNow;

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
    
    UIPinchGestureRecognizer* pinch = [[UIPinchGestureRecognizer alloc]initWithTarget:self action:@selector(pinchAction:)];
    [self addGestureRecognizer:pinch];
    
    self.backgroundColor = UIColor.whiteColor;
    
}

-(void) pinchAction:(UIPinchGestureRecognizer*)gesture {
    if (gesture.state == UIGestureRecognizerStateBegan) {
        _startScale = gesture.scale;
    } else if (gesture.state == UIGestureRecognizerStateChanged) {
        [self updateFrame:gesture.scale/_startScale];
        _startScale = gesture.scale;
    }
}

-(void) updateFrame:(CGFloat)scale {
    CGFloat updateRulerWidth = _rulerLayer.bounds.size.width * scale;
    if (updateRulerWidth < (CGRectGetWidth(self.bounds) + 2 * TimeRulerLayer.sideOffset)){
        updateRulerWidth = (CGRectGetWidth(self.bounds) + 2 * TimeRulerLayer.sideOffset);
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
    _rulerLayer.showTopMark = YES;
    _rulerLayer.showBottomMark = NO;
    [_scrollView.layer addSublayer:_rulerLayer];
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
        _indicatorView.frame = CGRectMake(size.width * 0.5 - 2/ 2.0, strRect.size.height + 4, 2, self.indicatorLength);
        _indicatorView.layer.cornerRadius = 2;
        [_indicatorView setImage:nil];
        _indicatorView.backgroundColor = HSColorScheme.colorBlue;
        _rulerBackgroundView.hidden = YES;
        //end by 547
    }
    else {
        _indicatorView.frame = CGRectMake(size.width * 0.5 -  8/ 2.0, size.height - self.indicatorLength, 8, self.indicatorLength);
        [_indicatorView setImage:[UIImage imageNamed:@"icon_sjz_axis"]];
        _indicatorView.backgroundColor = UIColor.clearColor;
        _rulerBackgroundView.hidden = YES;
    }
}

//指示器长度
- (CGFloat)indicatorLength {
    if (_indicatorLength <= 0) {
        if(_style == TimeRulerStyleDefault){
            //modify by 547
            NSDictionary *strAttributes = @{NSFontAttributeName: [UIFont systemFontOfSize:kScaleDefaultFontSize]};;
            NSString *str = [self timeFormatted:0];
            CGRect strRect = [str boundingRectWithSize:CGSizeMake(MAXFLOAT, MAXFLOAT)
                                               options:NSStringDrawingUsesLineFragmentOrigin
                                            attributes:strAttributes
                                               context:nil];
            _indicatorLength = self.bounds.size.height - strRect.size.height - 4;
            //end by 547
        }
        else{
            _indicatorLength = self.bounds.size.height - 2;
        }
    }
    return _indicatorLength;
}


- (NSString *)timeFormatted:(int)totalSeconds{
    
    //int seconds = totalSeconds % 60;
    int minutes = (totalSeconds / 60) % 60;
    int hours = totalSeconds / 3600;
    
    return [NSString stringWithFormat:@"%02d:%02d",hours, minutes];
    
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    CGFloat sideInset = CGRectGetWidth(self.bounds) / 2.0;
    
    _scrollView.frame = self.bounds;
    _scrollView.contentInset = UIEdgeInsetsMake(0, sideInset - TimeRulerLayer.sideOffset, 0, sideInset - TimeRulerLayer.sideOffset);
    
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

-(CGPoint) contentOffset:(int)current {
    CGFloat proportion = current / (24 * 3600.0);
    CGFloat proportionWidth = (_scrollView.contentSize.width - TimeRulerLayer.sideOffset * 2) * proportion;
    return CGPointMake(proportionWidth - _scrollView.contentInset.left, _scrollView.contentOffset.y);
}

#pragma mark UIScrollViewDelegate
- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView {
    _isTouch = YES;
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView {
    
    // 缩放过程中，不做滚动处理。（避免浮点型误差导致的中心移动）
    if (_isScaleJustNow) {
        double dis = CFAbsoluteTimeGetCurrent() - _scaleTimestamp;
        _isScaleJustNow = NO;
        NSLog(@"scrollViewDidScroll dis:%f", dis);
        if (dis < 0.1) {
            return;
        }
    }
    
    CGFloat proportionWidth = scrollView.contentOffset.x + scrollView.contentInset.left;
    CGFloat proportion = proportionWidth / (scrollView.contentSize.width - TimeRulerLayer.sideOffset * 2);
    int value = (int)ceil(proportion * 24 * 3600);
    NSLog(@"scrollViewDidScroll value:%d  proportionWidth:%f, proportion:%f", value, proportionWidth, proportion);
    _currentTime = value;
}

- (void)scrollViewDidEndDecelerating:(UIScrollView *)scrollView {
    _isTouch = NO;
}

- (void)scrollViewDidEndDragging:(UIScrollView *)scrollView willDecelerate:(BOOL)decelerate {
    if (!decelerate) {
        _isTouch = NO;
    }
}

@end
