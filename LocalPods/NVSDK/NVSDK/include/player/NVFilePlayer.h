#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AudioToolbox/AudioQueue.h>
#import "FilePlayerDelegate.h"

@interface NVFilePlayer : UIView
@property (weak) id<FilePlayerDelegate> playDelegate;
@property (nonatomic,weak) UILabel *timestampLabel;
@property (nonatomic,assign) CGFloat speed;
@property (nonatomic,assign) BOOL isNeedClean;
@property (nonatomic,assign) BOOL stretch;

- (UIView *)view;

- (BOOL) play:(NSString*)path Duration:(int)duration;
- (BOOL) play:(NSString*)path Duration:(int)duration Mute:(BOOL)mute Speed:(CGFloat)speed;
- (BOOL) stop;
- (void) seek:(int)pec;
- (void) pause;
- (void) resume;
- (void) mute:(BOOL)isMute;

- (void) onApplicationDidBecomeActive;
- (void) onApplicationWillResignActive;
- (UIImage*) screenShot;//add by luo 20141120
- (UIImage *)screenShot2;
- (void) setCamType:(int)nCamType;
- (void) InitFisheyeParam:(int)iFixType andCenterX:(int) xCenter andCenterY:(int)yCenter andRadius:(int)radius ;
- (void) SetImageYUV:(int)RGBorYUV420 andImageBuffer:(Byte *) pData andWidth:(int) width andHeight:(int) height;
- (void) SetMode:(int) iMode;
- (void) Clearsurface;//RGB图片预览下一张加载过程的清屏工作
- (void) SetActive: (BOOL) bActive;
- (void) resetRowColumn;
- (void) repaint;
- (void) releasePanoView;
- (BOOL)onDblClickView:(CGFloat)x y:(CGFloat)y;

@end      
