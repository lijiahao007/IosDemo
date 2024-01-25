//
//  StackViewDemoViewController.m
//  MyApplication
//
//  Created by 李嘉浩 on 2024/1/7.
//

#import "StackViewDemoViewController.h"
/**
 总结：
 1. UIStackView内部管理子View布局的方法是约束。我们如果要设置View的布局，也要使用约束
 
 
 */
@interface StackViewDemoViewController ()

@property (nonatomic, strong) UIStackView* stackView1;

@end

@implementation StackViewDemoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    _stackView1 = [[UIStackView alloc]initWithFrame:CGRectMake(20, 100, kWidth - 40, 100)];
    _stackView1.alignment = UIStackViewAlignmentCenter;
    
    /**
     决定子View的填充方式，用约束的方法来设置的 （以UILayoutConstraintAxisHorizontal为例分析一下。）
     UIStackViewDistributionFill:  让子View来填充满整个
        1. UIStackView.leading == firstView. leading
        2. UIStackView.trailing == lastView.trailing
        
     
     */
    _stackView1.distribution = UIStackViewDistributionFill;
    _stackView1.axis = UILayoutConstraintAxisHorizontal;
    [self.view addSubview:_stackView1];

    UIView* view1 = [[UIView alloc]init];
    view1.backgroundColor = [UIColor redColor];

    [view1 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(50);
//        make.width.mas_equalTo(40);
    }];
    [_stackView1 addArrangedSubview:view1];
    
    UIView* view2 = [[UIView alloc]init];
    view2.backgroundColor = [UIColor blueColor];
//    [view2 setContentHuggingPriority:750 forAxis:UILayoutConstraintAxisHorizontal];
//    [view2 setContentCompressionResistancePriority:750 forAxis:UILayoutConstraintAxisHorizontal];
    [view2 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(70);
//        make.width.mas_equalTo(40);
    }];
    [_stackView1 addArrangedSubview:view2];
    
    
    UIView* view3 = [[UIView alloc]init];
    view3.backgroundColor = [UIColor greenColor];
//    [view3 setContentHuggingPriority:749 forAxis:UILayoutConstraintAxisHorizontal];
//    [view3 setContentCompressionResistancePriority:749 forAxis:UILayoutConstraintAxisHorizontal];
    [view3 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(60);
//        make.width.mas_equalTo(40);
    }];
    [_stackView1 addArrangedSubview:view3];
    
}

#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    NSLog(@"prepareForSegue 【%@】", NSStringFromClass([self class]));
}

@end
