//
//  TimelineViewController.m
//  MyApplication
//
//  Created by HS on 2024/10/23.
//

#import "TimelineViewController.h"
#import "TimeRuler.h"
#import "TimeRulerInfo.h"
@interface TimelineViewController ()
@property (nonatomic, strong) TimeRuler* timeRuler;
@end

@implementation TimelineViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // 设置背景颜色为白色
    self.view.backgroundColor = [UIColor whiteColor];
    
//    // 创建 TimeRuler 实例并设置其 frame
    _timeRuler = [[TimeRuler alloc] initWithFrame:CGRectMake(0, CGRectGetHeight(self.view.bounds) * 0.5 - 40.0, CGRectGetWidth(self.view.bounds), 80.0)];
    
    
    NSArray* selectedArray = @[
        [[TimeRulerInfo alloc] initWithStartSecond:60 endSecond:300],
        [[TimeRulerInfo alloc] initWithStartSecond:500 endSecond:800],
        [[TimeRulerInfo alloc] initWithStartSecond:3600 endSecond:4800],
        [[TimeRulerInfo alloc] initWithStartSecond:8501 endSecond:10000],
        [[TimeRulerInfo alloc] initWithStartSecond:12000 endSecond:15797],
        [[TimeRulerInfo alloc] initWithStartSecond:18800 endSecond:20000],
        [[TimeRulerInfo alloc] initWithStartSecond:25000 endSecond:30000],
    ];

    // 设置选中的时间区间
    [_timeRuler setSelectedRange:selectedArray];
    // 将时间尺添加到当前视图
    [self.view addSubview:_timeRuler];
    
}

- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator {
    NSLog(@"viewWillTransitionToSize: size.width:%f size.height:%f", size.width, size.height);
    
    CGRect rect = _timeRuler.frame;
    rect.origin.y = size.height * 0.5 - 40.0;
    rect.size.width = size.width;
    _timeRuler.frame = rect;
    
}


@end
