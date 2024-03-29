//
//  HSFrameData.h
//
//  Created by Macrovideo on 2018/10/22.
//


#ifndef HS_FRAME_DATA
#define HS_FRAME_DATA

#define LIVE_VIDEO_NETWORK_QUEUE_SIZE 25
#define LIVE_VIDEO_DISPLAY_QUEUE_SIZE 20
#define LIVE_AUDIO_NETWORK_QUEUE_SIZE 10

enum MULTIMEDIA_TYPE{
    HSMT_UNKOW = 0,
    HSMT_VIDEO = 1,
    HSMT_AUDIO = 2,
    HSMT_THERAL = 3,
    HSMT_MSG = 4,
};

typedef struct tagFrameData{
     
    int fId;
    int channel;
    int width;
    int height;
    int64_t timestamp;
    
    int flag;
    int mediaType;
    int nType;
    int64_t nSize;
    uint8_t *data;
}HSFRAME_DATA, *PHSFRAME_DATA;


#endif

