//
//  TimerDemoViewController.m
//  MyApplication
//
//  Created by package on 2024/5/7.
//

#import "TimerDemoViewController.h"

@interface TimerDemoViewController ()

@end

@implementation TimerDemoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSLog(@"timer start %@", [NSThread currentThread]);
//    NSTimer* timer = [NSTimer scheduledTimerWithTimeInterval:1 repeats:YES block:^(NSTimer * _Nonnull timer) {
//        NSLog(@"timer fired!");
//    }];
//    
//    NSTimer* timer = [NSTimer timerWithTimeInterval:1 repeats:YES block:^(NSTimer * _Nonnull timer) {
//        NSLog(@"timer fired!");
//    }];
//    [[NSRunLoop mainRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
  
    NSTimer* timer = [[NSTimer alloc]initWithFireDate:[NSDate dateWithTimeIntervalSinceNow:3] interval:1 repeats:YES block:^(NSTimer * _Nonnull timer) {
        NSLog(@"timer fired! %@", [NSThread currentThread]);
    }];
    [[NSRunLoop mainRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];

    
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [timer invalidate];
        [timer invalidate];
        NSLog(@"timer end %@", [NSThread currentThread]);
    });
    
}


@end
