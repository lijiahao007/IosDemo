//
//  SegmentViewController.m
//  MyApplication
//
//  Created by 李嘉浩 on 2024/1/25.
//

#import "SegmentViewController.h"
#import "JXCategoryView.h"

@interface SegmentViewController () <JXCategoryViewDelegate>

@property (nonatomic, strong) JXCategoryTitleView*	categoryView;
@property (nonatomic, strong) JXCategoryIndicatorLineView* indicatorLineView;
@end

@implementation SegmentViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.categoryView = [[JXCategoryTitleView alloc] init];
    self.categoryView.delegate = self;
    self.categoryView.titles = @[@"手机注册", @"邮箱注册邮箱注册"];
    self.categoryView.titleFont = [UIFont systemFontOfSize:15 weight:UIFontWeightMedium];
    self.categoryView.titleColor = [UIColor orangeColor];
    
    CGFloat totalWidth = 0;
    for (int i = 0; i < self.categoryView.titles.count; i++) {
        NSString* title = self.categoryView.titles[i];
        CGRect rect = [title boundingRectWithSize:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX) options:NSStringDrawingUsesLineFragmentOrigin attributes:@{
                    NSFontAttributeName: [UIFont systemFontOfSize:15 weight:UIFontWeightMedium]
        } context:nil];
        NSLog(@"%@ size [%f, %f]", title, rect.size.width, rect.size.height);
        totalWidth += rect.size.width;
        totalWidth += 15;
    }
    totalWidth += 20;
    
    if (totalWidth > kWidth - 32) {
        totalWidth = kWidth - 32;
    }
    
    self.categoryView.backgroundColor = [[UIColor blueColor]colorWithAlphaComponent:0.2];
    self.categoryView.cellSpacing = 15;
    [self.view addSubview:self.categoryView];
    
    [self.categoryView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.mas_equalTo(100);
        make.leading.mas_equalTo(16);
        make.width.mas_equalTo(totalWidth);
        make.height.mas_equalTo(40);
    }];
    
    self.indicatorLineView = [[JXCategoryIndicatorLineView alloc]init];
    self.indicatorLineView.indicatorWidth = JXCategoryViewAutomaticDimension;
    self.categoryView.indicators = @[self.indicatorLineView];
}

#pragma JXCategoryViewDelegate
- (void)categoryView:(JXCategoryBaseView *)categoryView didSelectedItemAtIndex:(NSInteger)index {
    NSLog(@"didSelect index[%ld]", index);
}

@end
