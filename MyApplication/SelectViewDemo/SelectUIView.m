//
//  SelectUIView.m
//  MyApplication
//
//  Created by package on 2024/5/7.
//

#import "SelectUIView.h"

@implementation SelectUIView



- (void)drawRect:(CGRect)rect {
//    [self drawMyRect:CGRectMake(10, 10, 100, 100) color:[UIColor redColor]];
    [self drawMyRect:CGRectMake(13, 13, 94, 94) color:[UIColor blueColor]];
}


- (void)drawMyRect:(CGRect)rect color:(UIColor*)color {
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    // 设置填充颜色
    CGContextSetFillColorWithColor(context, color.CGColor);
    
    // 设置边框颜色
    CGContextSetStrokeColorWithColor(context, [UIColor redColor].CGColor);
    
    // 创建并绘制矩形
    
    // 填充矩形
    CGContextFillRect(context, rect);
    
//    // 绘制矩形边框
    CGContextStrokeRect(context, rect);
}

@end
