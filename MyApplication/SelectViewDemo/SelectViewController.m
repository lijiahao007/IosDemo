//
//  SelectViewController.m
//  MyApplication
//
//  Created by package on 2024/5/7.
//

#import "SelectViewController.h"
#import "SelectUIView.h"

@interface SelectViewController ()

@end

@implementation SelectViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    SelectUIView* view = [[SelectUIView alloc]initWithFrame:self.view.bounds];
    [self.view addSubview:view];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
