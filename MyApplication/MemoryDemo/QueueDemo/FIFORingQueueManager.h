//
//  FIFORingQueueManager.h
//  NVSDK
//
//  Created by Macrovideo on 2018/7/26.
//  Copyright © 2018年 macrovideo. All rights reserved.
//

#ifndef FIFORingQueueManager_h
#define FIFORingQueueManager_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "string.h"
#include "QueueManageDefines.h"
#include "HSFrameData.h"

#ifdef __cplusplus
extern "C" {
#endif
    


typedef struct _tagBufferManager{
    char *buffer;
    int64_t nBufferSize;
    int64_t nLestSize;
    int64_t nFront;
    int64_t nRear;
}BUFFER_MANAGER, *PBUFFER_MANAGER;

typedef struct  _tagRingNode{
    int nId;//
    int nFlag;
    int nMediaType;//
    int nType;//
    int nFrameRate;//
    int64_t nSize;//
    int64_t lTimestamp;
    int64_t nIndex;//
    int nWidth;
    int nHeight;
}RING_NODE,*PRING_NODE;

typedef struct _tagRingQueue{
    int nQueueSize; //
    PRING_NODE *queue;
    PBUFFER_MANAGER bufferManager;
    int nFront;
    int nRear;
    
    //video param
    int nWidth;
    int nHeight;
    
    //audio param
}FIFO_RING_QUEUE, *PFIFO_RING_QUEUE;

PFIFO_RING_QUEUE initRingQueue(int nLevel, int nQueueSize);
bool releaseRingQueue(PFIFO_RING_QUEUE ringQueue);

bool resetRingQueue(PFIFO_RING_QUEUE ringQueue);

bool isRingQueueEmpty(PFIFO_RING_QUEUE ringQueue);

bool setParamTORingQueue(PFIFO_RING_QUEUE ringQueue, int nWidth, int nHeight);
    
int putDataToQueue(PFIFO_RING_QUEUE ringQueue, const char *pData,  int nSize,  int nId, int nMediaType, int nType, int nFlag, int64_t lTimestamp, int nFrameRate , int width , int height);
int getDataFromQueue(PFIFO_RING_QUEUE ringQueue, const char *pData, int mediaInfos[], int64_t lTimestamp[]);

int putFrameToQueue(PFIFO_RING_QUEUE ringQueue, PHSFRAME_DATA pFrameData);
int getFrameFromQueue(PFIFO_RING_QUEUE ringQueue, PHSFRAME_DATA pFrameData);

int getTypeFromQueue(PFIFO_RING_QUEUE ringQueue);
int getMediaTypeFromQueue(PFIFO_RING_QUEUE ringQueue);
int64_t getTimestampFromQueue(PFIFO_RING_QUEUE ringQueue);
int getRingQueueSize(PFIFO_RING_QUEUE ringQueue);
int64_t getRingQueueDataSize(PFIFO_RING_QUEUE ringQueue);
#ifdef __cplusplus
}
#endif

#endif /* FIFORingQueueManager_h */

