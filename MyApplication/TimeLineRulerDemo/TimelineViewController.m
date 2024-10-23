//
//  TimelineViewController.m
//  MyApplication
//
//  Created by HS on 2024/10/23.
//

#import "TimelineViewController.h"
#import "TimelineView.h"

@interface TimelineViewController ()

@end

@implementation TimelineViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    TimelineView *timelineView = [[TimelineView alloc] initWithFrame:CGRectMake(0,
                                                                                   CGRectGetHeight(self.view.bounds) - 100,
                                                                                   CGRectGetWidth(self.view.bounds),
                                                                                   100)];
    timelineView.backgroundColor = [UIColor whiteColor];
    [self.view addSubview:timelineView];
}

@end
