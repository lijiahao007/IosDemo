//
//  StackViewDemoViewController.m
//  MyApplication
//
//  Created by 李嘉浩 on 2024/1/7.
//

#import "StackViewDemoViewController.h"
#import "UIView1.h"
#import "UIView2.h"
#import "UIView3.h"
#import "UILabel1.h"
#import "UILabel2.h"
#import "UILabel3.h"
#import "UIButton1.h"
#import "UIButton2.h"
#import "UIButton3.h"
#import "IntrinsicContentView.h"
/**
 总结：
 1. UIStackView内部管理子View布局的方法是约束。我们如果要设置View的布局，也要使用约束
 
 
 */
@interface StackViewDemoViewController ()

@property (nonatomic, strong) UIStackView* stackView1;
@property (nonatomic, strong) UIStackView* stackView2;

@end

@implementation StackViewDemoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
//    [self setStackViewDemo1];
    [self setStackViewDemo2];
}

- (void) setStackViewDemo2 {
    
    _stackView2 = [[UIStackView alloc]init];
    _stackView2.spacing = 10;
    _stackView2.alignment = UIStackViewAlignmentCenter;
    _stackView2.distribution = UIStackViewDistributionEqualSpacing;
    _stackView2.translatesAutoresizingMaskIntoConstraints = NO;
    _stackView2.backgroundColor = [UIColor yellowColor];
    [self.view addSubview:_stackView2];

    [_stackView2 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.trailing.equalTo(self.view).offset(-10);
        make.top.equalTo(self.view).offset(200);
        make.height.mas_equalTo(50);
    }];
    
    
    UIButton1* btn1 = [UIButton1 new];
    btn1.backgroundColor = [UIColor redColor];
    [btn1 setTitle:@"Button1" forState:UIControlStateNormal];
    
    UIButton2* btn2 = [UIButton2 new];
    btn2.backgroundColor = [UIColor blueColor];
    [btn2 setTitle:@"Button2" forState:UIControlStateNormal];
    
    UIButton3* btn3 = [UIButton3 new];
    btn3.backgroundColor = [UIColor greenColor];
    [btn3 setTitle:@"Button3" forState:UIControlStateNormal];
    
    [_stackView2 addArrangedSubview:btn1];
    [_stackView2 addArrangedSubview:btn2];
    [_stackView2 addArrangedSubview:btn3];
    
    NSArray<UIButton*>* btns = @[btn1, btn2, btn3];
    [btns enumerateObjectsUsingBlock:^(UIButton * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        obj.tag = idx;
        [obj addTarget:self action:@selector(onButtonClick:) forControlEvents:UIControlEventTouchUpInside];
    }];
    
    
    UIButton* btn = [UIButton new];
    btn.tag = 100;
    [btn setTitle:@"Clear" forState:UIControlStateNormal];
    [self.view addSubview:btn];
    [btn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.equalTo(self.view);
    }];
    
    [btn addTarget:self action:@selector(onButtonClick:) forControlEvents:UIControlEventTouchUpInside];
}
 

-(void) onButtonClick:(UIButton*)sender {
    if (sender.tag == 100) {
        [_stackView2.subviews enumerateObjectsUsingBlock:^(__kindof UIView * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
            obj.hidden = NO;
        }];
    } else if (sender.tag == 0 || sender.tag == 1 || sender.tag == 2) {
        sender.hidden = YES;
    }
}


-(void) setStackViewDemo1 {
    _stackView1 = [[UIStackView alloc]init];
    //    _stackView1.backgroundColor = [UIColor blueColor];
    _stackView1.alignment = UIStackViewAlignmentCenter;
    [self.view addSubview:_stackView1];
    [_stackView1 setLayoutMargins:UIEdgeInsetsMake(10, 8, 20, 5)];
    [_stackView1 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.mas_equalTo(self.view);
        make.width.mas_equalTo(kWidth - 40);
        //            make.height.mas_equalTo(100);
    }];
    
    /**
     决定子View的填充方式，用约束的方法来设置的 （以UILayoutConstraintAxisHorizontal为例分析一下。）
     UIStackViewDistributionFill:  让子View来填充满整个
     1. UIStackView.leading == firstView. leading
     2. UIStackView.trailing == lastView.trailing
     */
    _stackView1.distribution = UIStackViewDistributionFill;
    _stackView1.axis = UILayoutConstraintAxisHorizontal;
    
    [self setViewDemo];
    [self setLabelDemo];
    [self setViewDemo2];
    [self setIntrinsicContentViewDemo];
    
}


- (void) setViewDemo {
    // UIView
    UIView1* view1 = [UIView1 new];
    view1.backgroundColor = [UIColor redColor];
    
    UIView2* view2 = [UIView2 new];
    view2.backgroundColor = [UIColor greenColor];
    
    UIView3* view3 = [UIView3 new];
    view3.backgroundColor = [UIColor blueColor];
    
    [_stackView1 addArrangedSubview:view1];
    [_stackView1 addArrangedSubview:view2];
    [_stackView1 addArrangedSubview:view3];
    
    [view1 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(80);
        make.width.mas_equalTo(100).priority(999);
    }];
    
    [view2 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(120);
        make.width.mas_equalTo(100).priority(999);
        
    }];
    
    [view3 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(50);
        make.width.mas_equalTo(100).priority(999);
    }];
}

-(void) setLabelDemo {
    //         UILabel
    UILabel1* label1 = [[UILabel1 alloc]init];
    label1.text = @"label1";
    label1.backgroundColor = [UIColor redColor];
    [label1 setContentHuggingPriority:800 forAxis:UILayoutConstraintAxisHorizontal];
    [label1 setContentCompressionResistancePriority:800 forAxis:UILayoutConstraintAxisHorizontal];
    [_stackView1 addArrangedSubview:label1];
    
    
    UILabel2* label2 = [[UILabel2 alloc]init];
    label2.text = @"label2";
    label2.backgroundColor = [UIColor blueColor];
    [label2 setContentHuggingPriority:700 forAxis:UILayoutConstraintAxisHorizontal];
    [label2 setContentCompressionResistancePriority:700 forAxis:UILayoutConstraintAxisHorizontal];
    
    [_stackView1 addArrangedSubview:label2];
    
    UILabel3* label3 = [[UILabel3 alloc]init];
    
    label3.text = @"label3";
    label3.backgroundColor = [UIColor greenColor];
    [label3 setContentHuggingPriority:400 forAxis:UILayoutConstraintAxisHorizontal];
    [label3 setContentCompressionResistancePriority:400 forAxis:UILayoutConstraintAxisHorizontal];
    
    [_stackView1 addArrangedSubview:label3];
}

-(void) setViewDemo2 {
    UIView1* view1 = [UIView1 new];
    view1.backgroundColor = [UIColor redColor];

    UIView2* view2 = [UIView2 new];
    view2.backgroundColor = [UIColor blueColor];

    UIView3* view3 = [UIView3 new];
    view3.backgroundColor = [UIColor greenColor];


    [_stackView1 addArrangedSubview:view1];
    [_stackView1 addArrangedSubview:view2];
    [_stackView1 addArrangedSubview:view3];


    [view1 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(50);
        make.width.mas_equalTo(80);
    }];


    [view2 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(60);
        make.width.mas_equalTo(20);
    }];

    [view3 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(80);
        make.width.mas_equalTo(120);
    }];

}

-(void) setIntrinsicContentViewDemo {
    IntrinsicContentView* view1 = [[IntrinsicContentView alloc]initWithFrame:CGRectMake(0, 0, 100, 80)];
    view1.backgroundColor = [UIColor redColor];
    [view1 setContentHuggingPriority:800 forAxis:UILayoutConstraintAxisHorizontal];
    [view1 setContentCompressionResistancePriority:800 forAxis:UILayoutConstraintAxisHorizontal];
    [_stackView1 addArrangedSubview:view1];


    IntrinsicContentView* view2 =  [[IntrinsicContentView alloc]initWithFrame:CGRectMake(0, 0, 100, 120)];
    view2.backgroundColor = [UIColor blueColor];
    [view2 setContentHuggingPriority:700 forAxis:UILayoutConstraintAxisHorizontal];
    [view2 setContentCompressionResistancePriority:700 forAxis:UILayoutConstraintAxisHorizontal];
    [_stackView1 addArrangedSubview:view2];

    IntrinsicContentView* view3 =  [[IntrinsicContentView alloc]initWithFrame:CGRectMake(0, 0, 100, 50)];
    view3.backgroundColor = [UIColor greenColor];
    [_stackView1 addArrangedSubview:view3];
    
}

- (void)viewDidLayoutSubviews {
    NSLog(@"%@\n", self.stackView1.constraints);
    
    for (UIView* view in self.stackView1.subviews) {
        NSLog(@"%@", view);
        for (NSLayoutConstraint* constraint in view.constraints) {
            NSLog(@"%@ -- %f -- %f", constraint, constraint.constant, constraint.priority);
        }
        NSLog(@"\n");
    }
}

#pragma mark - Navigation
// 跳转前调用？什么跳转前
// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    NSLog(@"prepareForSegue 【%@】", NSStringFromClass([self class]));
}

@end
