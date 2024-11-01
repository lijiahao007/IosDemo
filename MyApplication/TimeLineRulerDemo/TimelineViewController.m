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
    self.view.backgroundColor = [UIColor colorWithHex:0xfafafa];
    
//    // 创建 TimeRuler 实例并设置其 frame
    _timeRuler = [[TimeRuler alloc] initWithFrame:CGRectMake(0, CGRectGetHeight(self.view.bounds) * 0.5 - 50.0, CGRectGetWidth(self.view.bounds), 100.0)];
    
    _timeRuler.style = TimeRulerStyleDefault;
//    
//    NSArray* selectedArray = @[
//        [[TimeRulerInfo alloc] initWithStartSecond:60 endSecond:300 color:[HSColorScheme colorRedNormal] priority:1],
//        [[TimeRulerInfo alloc] initWithStartSecond:500 endSecond:800 color:[HSColorScheme colorBlue] priority:1],
//        [[TimeRulerInfo alloc] initWithStartSecond:3600 endSecond:4800 color:[HSColorScheme colorGreenLight] priority:1],
//        [[TimeRulerInfo alloc] initWithStartSecond:8501 endSecond:10000 color:[HSColorScheme colorBackground] priority:1],
//        [[TimeRulerInfo alloc] initWithStartSecond:12000 endSecond:15797 color:[HSColorScheme colorWithDarkModeRGB:0xff0000 lightColor:0x00ff00] priority:1],
//        [[TimeRulerInfo alloc] initWithStartSecond:18800 endSecond:20000 color:[HSColorScheme colorBlue] priority:1],
//        [[TimeRulerInfo alloc] initWithStartSecond:25000 endSecond:30000 color:[HSColorScheme colorRedHeavy] priority:1],
//        [[TimeRulerInfo alloc] initWithStartSecond:70000 endSecond:80000 color:[HSColorScheme colorBlue] priority:7],
//        [[TimeRulerInfo alloc] initWithStartSecond:50000 endSecond:86400 color:[HSColorScheme colorGreen] priority:1],
//    ];
//    
    NSMutableArray* selectedArray = [NSMutableArray array];
    for (int i = 0; i < 20; i++) {
        uint32_t startSecond = arc4random() % (24*3600);
        
        if (startSecond > 3600) {
            startSecond -= 3600;
        }
        
        uint32_t endSecond = startSecond + arc4random() % 3000 + 600;
        NSLog(@"{s:%u, e:%u}", startSecond, endSecond);
        UIColor* ranColor = [UIColor colorWithHex:arc4random()];
        TimeRulerInfo* info = [[TimeRulerInfo alloc] initWithStartSecond:startSecond endSecond:endSecond color:ranColor priority:1];
        [selectedArray addObject:info];
    }

    // 设置选中的时间区间
    [_timeRuler setSelectedRange:selectedArray];
    // 将时间尺添加到当前视图
    [self.view addSubview:_timeRuler];
    
}

- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator {
    NSLog(@"viewWillTransitionToSize: size.width:%f size.height:%f", size.width, size.height);
    
    CGRect rect = _timeRuler.frame;
    rect.size.width = size.width;
    
    if (size.width > size.height) {
        _timeRuler.style = TimeRulerStyleLandscape;
        rect.size.height = 80;
        rect.origin.y = size.height * 0.5 - 40.0;

    } else {
        _timeRuler.style = TimeRulerStyleDefault;
        rect.size.height = 80;
        rect.origin.y = size.height * 0.5 - 40.0;
    }
    
    _timeRuler.frame = rect;

}


@end
