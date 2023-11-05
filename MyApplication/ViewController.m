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

@interface ViewController () <UITableViewDelegate, UITableViewDataSource>
@property (nonatomic, strong) UITableView* tableView;
@property (nonatomic, strong) NSMutableArray* tableArray;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [HSColorScheme colorBackground];
    
    [self.tableArray addObjectsFromArray:@[@"Masonry"]];
    [self.tableArray addObjectsFromArray:@[@"YUVDemo"]];
    
    self.tableView = [[UITableView alloc]initWithFrame:CGRectMake(0, 0, kWidth, kHeight)];
    self.tableView.estimatedRowHeight = 70;
    self.tableView.dataSource = self;
    self.tableView.delegate = self;
    self.tableView.backgroundColor = [UIColor lightGrayColor];
    [self.view addSubview:self.tableView];
}

- (NSMutableArray *)tableArray {
    if (_tableArray == nil) {
        _tableArray = [NSMutableArray array];
    }
    return _tableArray;
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
    
    cell.textLabel.text = self.tableArray[indexPath.row];
    cell.textLabel.textColor = HSColorScheme.colorBlack;
    cell.layer.cornerRadius = 10;
    cell.backgroundColor = HSColorScheme.colorWhite;
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
    switch (indexPath.row) {
        case 0:{
            MasonryDemoViewController* vc = [MasonryDemoViewController new];
            [self.navigationController pushViewController:vc animated:YES];
            break;
        }
        case 1: {
            YUVDemoViewController* vc = [YUVDemoViewController new];
            [self.navigationController pushViewController:vc animated:YES];
            break;
        }
    }
}



@end
