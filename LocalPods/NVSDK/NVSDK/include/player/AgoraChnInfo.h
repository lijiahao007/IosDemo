//
//  AgoraChnInfo.h
//  NVSDK
//
//  Created by Yang on 2020/11/24.
//  Copyright © 2020 macrovideo. All rights reserved.
//

#import <Foundation/Foundation.h>
//@class AgoraLiveChn;
//@class AgoraPlaybackChn;
//@class AgoraDownloadChn;

@interface AgoraLiveChn: NSObject
@property (nonatomic,copy) NSString *name;
@property (nonatomic,assign) int ability;
@property (nonatomic,assign) int expireTime;
@property (nonatomic,copy) NSString *token;
@end

@interface AgoraPlaybackChn : NSObject
@property (nonatomic,copy) NSString *name;
@property (nonatomic,assign) int ability;
@property (nonatomic,assign) int expireTime;
@property (nonatomic,copy) NSString *token;
@end

@interface AgoraDownloadChn : NSObject
@property (nonatomic,copy) NSString *name;
@property (nonatomic,assign) int ability;
@property (nonatomic,assign) int expireTime;
@property (nonatomic,copy) NSString *token;
@end

@interface AgoraChnInfo : NSObject
@property (nonatomic, strong) AgoraLiveChn *liveChannel;
@property (nonatomic, strong) AgoraPlaybackChn *playbackChannel;
@property (nonatomic, strong) AgoraDownloadChn *downloadChannel;
@property (nonatomic, copy)NSString *rtmToken;
@end





