//
//  MasonryDemoViewController.m
//  MyApplication
//
//  Created by 李嘉浩 on 2023/10/12.
//

#import "MasonryDemoViewController.h"
#import "AppDelegate.h"
#import <Masonry/Masonry.h>
#import "UIView1.h"
#import "UIView2.h"
#import "UIView3.h"

@interface MasonryDemoViewController ()

@end

@implementation MasonryDemoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    [self createView];
}

-(void) createView {
    UIView* rootView = [[UIView alloc]initWithFrame:CGRectMake(50, 200, 0, 0)];
    [self.view addSubview:rootView];
    
    UIView* contentView = [UIView new];
    contentView.backgroundColor = [UIColor lightGrayColor];
    [rootView addSubview:contentView];
    [contentView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.mas_equalTo(contentView);
        make.bottom.mas_equalTo(contentView);
    }];
    
    UIView1* view1 = [UIView1 new];
    view1.backgroundColor = [UIColor redColor];
    [contentView addSubview:view1];
    [view1 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.mas_equalTo(contentView.mas_leadingMargin);
        make.width.mas_equalTo(50);
        make.height.mas_equalTo(100);
        make.top.mas_greaterThanOrEqualTo(contentView);
        make.bottom.mas_lessThanOrEqualTo(contentView);
    }];
    
    UIView2* view2 = [UIView2 new];
    view2.backgroundColor = [UIColor blueColor];
    [contentView addSubview:view2];
    [view2 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.mas_equalTo(view1.mas_trailing);
        make.width.mas_equalTo(130);
        make.height.mas_equalTo(69);
        make.centerY.mas_equalTo(view1);
        make.top.mas_greaterThanOrEqualTo(contentView);
        make.bottom.mas_lessThanOrEqualTo(contentView);
    }];
    
    UIView3* view3 = [UIView3 new];
    view3.backgroundColor = [UIColor greenColor];
    [contentView addSubview:view3];
    [view3 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.mas_equalTo(view2.mas_trailing);
        make.width.mas_equalTo(40);
        make.height.mas_equalTo(120);
        make.trailing.mas_equalTo(contentView.mas_trailingMargin);
        make.centerY.mas_equalTo(view1);
        make.top.mas_greaterThanOrEqualTo(contentView);
        make.bottom.mas_lessThanOrEqualTo(contentView);
    }];
}



@end
