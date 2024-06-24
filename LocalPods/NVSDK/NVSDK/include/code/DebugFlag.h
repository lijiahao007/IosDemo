//
//  DebugFlag.h
//  iCamSee
//
//  Created by macrovideo on 15/7/7.
//  Copyright (c) 2015年 macrovideo. All rights reserved.
//

#ifndef DebugFlag_h
#define DebugFlag_h

#define APP_DEBUG //app debug中

#define V380_DEBUG
#define XYS_DEBUG
#define WSQ_DEBUG
#define BLE_DEBUG

#ifdef V380_DEBUG
#define V380Log(...) NSLog((@"[V380] %@"), [NSString stringWithFormat:__VA_ARGS__])
#else
#define V380Log(...) {}
#endif

#ifdef XYS_DEBUG
#define XLog(...) NSLog((@"xys %@"), [NSString stringWithFormat:__VA_ARGS__])
#else
#define XLog(...)
#endif

#ifdef WSQ_DEBUG
#define WLog(...) NSLog((@"[WSQ] %@（%s-----%d）"), [NSString stringWithFormat:__VA_ARGS__], __func__, __LINE__)
#else
#define WLog(...)
#endif

#ifdef BLE_DEBUG
#define BLELOG(...) NSLog((@"BLEDEBUG %@"), [NSString stringWithFormat:__VA_ARGS__])
#else
#define BLELOG(...)
#endif

#endif
