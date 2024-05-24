//
//  ViewController.m
//  MyApplication
//
//  Created by 李嘉浩 on 2023/9/22.
//

#import "ViewController.h"
#import "Masonry.h"
#import "MasonryDemoViewController.h"
#import "YUVDemoViewController.h"
#import "AudioChatViewController.h"
#import "StackViewDemoViewController.h"
#import "SegmentViewController.h"
#import "StackViewWithScrollViewDemoViewController.h"
#import "MemoryDemo/MemoryDemoViewController.h"
#import "AudioDemo/AudioViewController.h"
#import "TimerDemo/TimerDemoViewController.h"
#import "SelectViewDemo/SelectViewController.h"

@interface ViewController () <UITableViewDelegate, UITableViewDataSource>
@property (nonatomic, strong) UITableView* tableView;
@property (nonatomic, strong) NSArray<NSDictionary*>* tableArray;
@end

#define kItemName @"kItemName"
#define kItemVc @"kItemVc"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [HSColorScheme colorBackground];
    
    self.tableArray = @[
        @{kItemName:@"Masonry", kItemVc:[MasonryDemoViewController class]},
        @{kItemName:@"YUVDemo", kItemVc:[YUVDemoViewController class]},
        @{kItemName:@"AudioChat", kItemVc:[AudioChatViewController class]},
        @{kItemName:@"StackView", kItemVc:[StackViewDemoViewController class]},
        @{kItemName:@"StackView with ScrollView", kItemVc:[StackViewWithScrollViewDemoViewController class]},
        @{kItemName:@"SegmentViewDemo", kItemVc:[SegmentViewController class]},
        @{kItemName:@"MemoryDemo", kItemVc:[MemoryDemoViewController class]},
        @{kItemName:@"AudioDemo", kItemVc:[AudioViewController class]},
        @{kItemName:@"TimerDemo", kItemVc:[TimerDemoViewController class]},
        @{kItemName:@"SelectDemo", kItemVc:[SelectViewController class]},
    ];

    
    self.tableView = [[UITableView alloc]initWithFrame:CGRectMake(0, 0, kWidth, kHeight)];
    self.tableView.estimatedRowHeight = 70;
    self.tableView.dataSource = self;
    self.tableView.delegate = self;
    self.tableView.backgroundColor = [UIColor lightGrayColor];
    [self.view addSubview:self.tableView];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.tableArray.count;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 50;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:@"cell"];
    if (cell == nil) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"cell"];
    }
    NSDictionary* dict = self.tableArray[indexPath.row];
    cell.textLabel.text = dict[kItemName];
    cell.textLabel.textColor = HSColorScheme.colorBlack;
    cell.layer.cornerRadius = 10;
    cell.backgroundColor = HSColorScheme.colorWhite;
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    return cell;
}

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (indexPath.row == self.tableArray.count - 1) {
        cell.separatorInset = UIEdgeInsetsMake(0, 0, 0, cell.bounds.size.width);
    } else {
        cell.separatorInset = UIEdgeInsetsMake(0, 10, 0, 10);
    }
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSDictionary* dict = self.tableArray[indexPath.row];
    UIViewController* vc = [dict[kItemVc] new];
    [self.navigationController pushViewController:vc animated:YES];
}



@end
