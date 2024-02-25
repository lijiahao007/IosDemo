//
//  InstrictionView.m
//  MyApplication
//
//  Created by 李嘉浩 on 2024/2/25.
//

#import "IntrinsicContentView.h"

@implementation IntrinsicContentView


- (CGSize)intrinsicContentSize {
    return CGSizeMake(CGRectGetWidth(self.frame), CGRectGetHeight(self.frame));
}

@end
