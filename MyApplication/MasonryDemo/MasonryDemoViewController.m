//
//  MasonryDemoViewController.m
//  MyApplication
//
//  Created by 李嘉浩 on 2023/10/12.
//

#import "MasonryDemoViewController.h"
#import "AppDelegate.h"
#import <Masonry/Masonry.h>

@interface MasonryDemoViewController ()
@property (nonatomic, strong) UIView* fatherVhew;
@property (nonatomic, strong) UIView* sonView;
@property (nonatomic, strong) UIView* sonView1;

@end

@implementation MasonryDemoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    self.fatherVhew = [[UIView alloc] initWithFrame:CGRectZero];
    self.fatherVhew.backgroundColor = [UIColor blueColor];
    [self.view addSubview:self.fatherVhew];

    self.sonView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 50, 50)];
    [self.fatherVhew addSubview:self.sonView];
    self.sonView.backgroundColor = [UIColor redColor];

    self.sonView1 = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 50, 50)];
    [self.fatherVhew addSubview:self.sonView1];
    self.sonView1.backgroundColor = [UIColor greenColor];

    [self.sonView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.width.mas_equalTo(50);
        make.leading.top.mas_equalTo(self.fatherVhew).offset(100); //
    }];

    [self.sonView1 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.mas_equalTo(self.sonView.mas_trailing).offset(-10);
        make.top.mas_equalTo(self.sonView).offset(10);
        make.height.width.mas_equalTo(50);
    }];

    [self.fatherVhew mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.top.mas_equalTo(self.view).offset(50);
        make.leading.top.mas_lessThanOrEqualTo(self.sonView).offset(-10);
        make.bottom.trailing.mas_greaterThanOrEqualTo(self.sonView).offset(10);
        make.leading.top.mas_lessThanOrEqualTo(self.sonView1).offset(-10);
        make.bottom.trailing.mas_greaterThanOrEqualTo(self.sonView1).offset(10);
    }];
}


@end
