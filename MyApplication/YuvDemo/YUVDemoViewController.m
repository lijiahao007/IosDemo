//
//  YUVDemoViewController.m
//  MyApplication
//
//  Created by 李嘉浩 on 2023/10/16.
//

#import "YUVDemoViewController.h"
#import <Masonry/Masonry.h>
#import "yuv_compress.h"

/**
 TODO: 完成一个YUV、RGB图片的转换、变换展示demo
 */
@interface YUVDemoViewController () <UIImagePickerControllerDelegate, UINavigationControllerDelegate>
@property (nonatomic, strong) UIImagePickerController* imagePicker;

@property (nonatomic, strong) UIButton* selectPicBtn;
@property (nonatomic, strong) UIButton* convertBtn;
@property (nonatomic, strong) UIImageView* imageView;

@property (nonatomic, strong) UIImage* selectedImage;
@end

@implementation YUVDemoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self createView];
    
    // 1. 读取相册的图片 完成
    // 2. 缓存图片 完成
    // 3. 显示图片 完成
    // 4. 将图片转成yuv格式
        // 4.1 将jpeg格式的图片转成RGBA格式的原始数据。（利用UIImage可以完成）
        // 4.2 利用libyuv将RGB原始数据转成YUV格式
    // 5. 在将YUV格式转回RGB，然后显示图片

    
}

-(void) createView {
    self.view.backgroundColor = [HSColorScheme colorBackground];
    
    _selectPicBtn = [[UIButton alloc]init];
    [_selectPicBtn addTarget:self action:@selector(presentPhotoSelector) forControlEvents:UIControlEventTouchUpInside];
    [_selectPicBtn setTitle:@"选择图片" forState:UIControlStateNormal];
    [_selectPicBtn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [self.view addSubview:_selectPicBtn];
 
    _convertBtn = [[UIButton alloc]init];
    [_convertBtn addTarget:self action:@selector(convert) forControlEvents:UIControlEventTouchUpInside];
    [_convertBtn setTitle:@"转换图片" forState:UIControlStateNormal];
    [_convertBtn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [self.view addSubview:_convertBtn];
    
    [_selectPicBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.mas_equalTo(self.view);
        make.trailing.mas_equalTo(_convertBtn.mas_leading);
        make.bottom.mas_equalTo(self.view.mas_safeAreaLayoutGuideBottom).offset(-20);
        make.width.mas_equalTo(_convertBtn);
    }];
    
    [_convertBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.trailing.mas_equalTo(self.view);
        make.bottom.mas_equalTo(self.view.mas_safeAreaLayoutGuideBottom).offset(-20);
    }];
    
    _imageView = [[UIImageView alloc]init];
    _imageView.backgroundColor = HSColorScheme.colorGrayLight;
    _imageView.contentMode = UIViewContentModeScaleAspectFit;
    [self.view addSubview:_imageView];
    [_imageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.mas_equalTo(self.view.mas_safeAreaLayoutGuideTop);
            make.left.mas_equalTo(self.view.mas_safeAreaLayoutGuideLeft);
            make.right.mas_equalTo(self.view.mas_safeAreaLayoutGuideRight);
            make.bottom.mas_equalTo(_selectPicBtn.mas_top).offset(-10);
    }];
    
    
}
 
- (UIImagePickerController *)imagePicker {
    if (_imagePicker == nil) {
        _imagePicker = [[UIImagePickerController alloc] init];
        _imagePicker.delegate = self;
    }
    return _imagePicker;
}

-(void) convert {
    if (self.selectedImage == nil) return;
    
    [self convertJpegToYuv:self.selectedImage];
}


-(uint8_t*) convertJpegToYuv:(UIImage*)image {
    CGImageRef cgImage = image.CGImage;
    size_t width = CGImageGetWidth(cgImage);
    size_t height = CGImageGetHeight(cgImage);

    // 创建一个位图上下文来绘制图像
    CGContextRef context = CGBitmapContextCreate(NULL, width, height, 8, 0, CGColorSpaceCreateDeviceRGB(), kCGBitmapByteOrder32Big | kCGImageAlphaPremultipliedLast);

    // 在位图上下文中绘制图像
    CGContextDrawImage(context, CGRectMake(0, 0, width, height), cgImage);

    // 获取位图上下文中的图像数据
    unsigned char *rawData = CGBitmapContextGetData(context);
    
    unsigned char *yuvData = (unsigned char*)malloc(width * height * 3 / 2);
    

    
    
    CGContextRelease(context);
    return rawData;
}

#pragma mark - UIImagePickerControllerDelegate

-(void) presentPhotoSelector {
    [self presentViewController:self.imagePicker animated:YES completion:nil];
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<UIImagePickerControllerInfoKey,id> *)info {
    id media = info[UIImagePickerControllerOriginalImage];
    if ([media isKindOfClass:[UIImage class]]) {
        UIImage* image = media;
        NSLog(@"选择图片：%f %f", image.size.width, image.size.height);
        [_imageView setImage:image];
        self.selectedImage = image;
    }
}




@end
