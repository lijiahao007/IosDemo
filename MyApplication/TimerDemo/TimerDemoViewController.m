//
//  TimerDemoViewController.m
//  MyApplication
//
//  Created by package on 2024/5/7.
//

#import "TimerDemoViewController.h"
#import <mach/mach.h>

@interface TimerDemoViewController ()
@property (nonatomic, strong) NSDateFormatter *tempFormatter;
@end

@implementation TimerDemoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //    NSLog(@"timer start %@", [NSThread currentThread]);
    //    NSTimer* timer = [NSTimer scheduledTimerWithTimeInterval:1 repeats:YES block:^(NSTimer * _Nonnull timer) {
    //        NSLog(@"timer fired!");
    //    }];
    //
    X_WeakSelf
    NSTimer* timer = [NSTimer timerWithTimeInterval:1 repeats:YES block:^(NSTimer * _Nonnull timer) {
        X_StrongSelf
        

    }];
    [[NSRunLoop mainRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
    
    //    NSTimer* timer = [[NSTimer alloc]initWithFireDate:[NSDate dateWithTimeIntervalSinceNow:3] interval:1 repeats:YES block:^(NSTimer * _Nonnull timer) {
    //        NSLog(@"timer fired! %@", [NSThread currentThread]);
    //    }];
    //    [[NSRunLoop mainRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
    //
    //
    //
    //    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
    //        [timer invalidate];
    //        [timer invalidate];
    //        NSLog(@"timer end %@", [NSThread currentThread]);
    //    });
    //
    //    [self tsDemo: 1731555379879.0 / 1000.0];
    //    [self tsDemo:[[NSDate date] timeIntervalSince1970]];
    //
    //    _tempFormatter = [[NSDateFormatter alloc]init];
    //    _tempFormatter.dateFormat = @"YYYY-MM-dd HH:mm:ss.SSS";
    //    _tempFormatter.timeZone = [NSTimeZone timeZoneWithName:@"UTC"];
    //    NSString* str = [_tempFormatter stringFromDate:[NSDate dateWithTimeIntervalSince1970:1731956771.271]];
    //    NSLog(@"123 456 %@", str);
    //
    int a = 100;
    NSNumber* aNum = @(a);
    double b = [aNum doubleValue];
    NSLog(@"%d %@ %f", a, aNum, b);
    
    [[[NSThread alloc]initWithBlock:^{
        [[NSThread currentThread] setName:@"Test"];
        int index =  0;
        int count = 0;
        while (true) {
            index++;
            if (index % 100000 == 0) {
                usleep(10);
                index = 0;
                count++;
                if (count % 100000 == 0) {
                    usleep(1000000);
                }
            }
        }
    }] start];
}

- (NSString *)cpuUsage
{
    kern_return_t kr;
    task_info_data_t tinfo;
    mach_msg_type_number_t task_info_count;
    
    task_info_count = TASK_INFO_MAX;
    kr = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)tinfo, &task_info_count);
    if (kr != KERN_SUCCESS)
    {
        return @"NA";
    }
    
    task_basic_info_t      basic_info;
    thread_array_t         thread_list;
    mach_msg_type_number_t thread_count;
    thread_info_data_t     thinfo;
    mach_msg_type_number_t thread_info_count;
    thread_basic_info_t basic_info_th;
    uint32_t stat_thread = 0; // Mach threads
    
    basic_info = (task_basic_info_t)tinfo;
    
    // get threads in the task
    kr = task_threads(mach_task_self(), &thread_list, &thread_count);
    if (kr != KERN_SUCCESS)
    {
        return @"NA";
    }
    if (thread_count > 0)
        stat_thread += thread_count;
    
    long tot_idle = 0;
    long tot_user = 0;
    long tot_kernel = 0;
    int j;
    
    for (j = 0; j < thread_count; j++)
    {
        thread_info_count = THREAD_INFO_MAX;
        kr = thread_info(thread_list[j], THREAD_BASIC_INFO,
                         (thread_info_t)thinfo, &thread_info_count);
        if (kr != KERN_SUCCESS)
        {
            return nil;
        }
        
        basic_info_th = (thread_basic_info_t)thinfo;
        
        if (basic_info_th->flags & TH_FLAGS_IDLE)
        {
            //This is idle
            tot_idle = tot_idle + basic_info_th->user_time.microseconds + basic_info_th->system_time.microseconds;
        } else {
            //This is user
            tot_user = tot_user + basic_info_th->user_time.microseconds;
            
            //This is kernel
            tot_kernel = tot_kernel + basic_info_th->system_time.microseconds;
        }
        
    } // for each thread
    
    kr = vm_deallocate(mach_task_self(), (vm_offset_t)thread_list, thread_count * sizeof(thread_t));
    assert(kr == KERN_SUCCESS);
    
    long tot_cpu = tot_idle + tot_user + tot_kernel;
    
    return [NSString stringWithFormat:@"Idle: %.2f, User: %.2f, Kernel: %.2f", tot_idle*1.0/tot_cpu, tot_user*1.0/tot_cpu, tot_kernel*1.0/tot_cpu];
}

-(void) tsDemo:(NSTimeInterval)timestamp {
    
    NSDate *date = [NSDate dateWithTimeIntervalSince1970:timestamp];
    
    // 创建日期格式化器的基本配置
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"yyyy-MM-dd HH:mm:ss Z"];  // Z显示时区偏移
    
    // 测试不同时区
    NSArray *timeZones = @[
        [NSTimeZone timeZoneWithAbbreviation:@"UTC"],    // UTC+0
        [NSTimeZone timeZoneWithName:@"Asia/Shanghai"],  // UTC+8
        [NSTimeZone timeZoneWithName:@"America/New_York"],  // UTC-4/-5
        [NSTimeZone timeZoneWithName:@"Asia/Tokyo"],     // UTC+9
        [NSTimeZone timeZoneWithName:@"Europe/London"]   // UTC+1/+0
    ];
    
    NSLog(@"原始时间戳: %f", timestamp);
    NSLog(@"对应UTC时间: %@\n", date);
    
    for (NSTimeZone *timeZone in timeZones) {
        [formatter setTimeZone:timeZone];
        NSString *formattedDate = [formatter stringFromDate:date];
        NSLog(@"\t时区: %-20s 格式化结果: %@",
              [[timeZone name] UTF8String],
              formattedDate);
        
        // 演示解析回Date对象
        NSDate *parsedDate = [formatter dateFromString:formattedDate];
        NSLog(@"\t解析回时间戳: %f\n", [parsedDate timeIntervalSince1970]);
    }
    
    // 演示本地时区
    [formatter setTimeZone:[NSTimeZone localTimeZone]];
    NSLog(@"\t本地时区: %-20s 格式化结果: %@",
          [[[NSTimeZone localTimeZone] name] UTF8String],
          [formatter stringFromDate:date]);
}


@end
