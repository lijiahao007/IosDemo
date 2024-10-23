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

@property (nonatomic, strong) UIButton* button;

@end

@implementation MasonryDemoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
//    [self createView];
//    [self createButton];
    [self createScrollView];
}

-(void) createView {
    UIView* contentView = [UIView new];
    contentView.backgroundColor = [UIColor lightGrayColor];
    [self.view addSubview:contentView];
    [contentView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.mas_equalTo(self.view).offset(200);
        make.leading.mas_equalTo(self.view).offset(100);
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
        make.top.mas_equalTo(contentView).priority(249);
        make.bottom.mas_equalTo(contentView).priority(249);
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
        make.top.mas_equalTo(contentView).priority(249);
        make.bottom.mas_equalTo(contentView).priority(249);
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
        make.top.mas_equalTo(contentView).priority(249);
        make.bottom.mas_equalTo(contentView).priority(249);

    }];
}

-(void) createButton {
    UIImage* image = [UIImage imageNamed:@"control_icon_clock_endtime"];
    _button = [[UIButton alloc]initWithFrame:CGRectMake(0, 0, CGImageGetWidth(image.CGImage), CGImageGetHeight(image.CGImage))];
//    [_button setTitle:@"Helloworld" forState:UIControlStateNormal];
    [_button setImage:image forState:UIControlStateNormal];
    [self.view addSubview:_button];
}

-(void) createScrollView {
    UIView* view = [[NSBundle mainBundle]loadNibNamed:@"DemoView1" owner:nil options:nil].firstObject;
    view.frame = self.view.bounds;

    [self.view addSubview:view];
}



@end
