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

@end

@implementation MasonryDemoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    
    
    [self createView1];
    
    [self createView2];
    
   
}


-(void) createView2 {
    
}


-(void) createView1 {
    self.fatherVhew = [[UIView alloc] initWithFrame:CGRectZero];
    self.fatherVhew.backgroundColor = [UIColor blueColor];
    [self.view addSubview:self.fatherVhew];

    UIView* sonView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 50, 50)];
    [self.fatherVhew addSubview:sonView];
    sonView.backgroundColor = [UIColor redColor];

    UIView* sonView1 = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 50, 50)];
    [self.fatherVhew addSubview:sonView1];
    sonView1.backgroundColor = [UIColor greenColor];

    [sonView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.width.mas_equalTo(50);
        make.leading.top.mas_equalTo(self.fatherVhew).offset(100); //
    }];

    [sonView1 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.mas_equalTo(sonView.mas_trailing).offset(-10);
        make.top.mas_equalTo(sonView).offset(10);
        make.height.width.mas_equalTo(50);
    }];

    [self.fatherVhew mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.top.mas_equalTo(self.view).offset(50);
        make.leading.top.mas_lessThanOrEqualTo(sonView).offset(-10);
        make.bottom.trailing.mas_greaterThanOrEqualTo(sonView).offset(10);
        make.leading.top.mas_lessThanOrEqualTo(sonView1).offset(-10);
        make.bottom.trailing.mas_greaterThanOrEqualTo(sonView1).offset(10);
    }];
    
    self.fatherVhew.hidden = YES;
}

@end
