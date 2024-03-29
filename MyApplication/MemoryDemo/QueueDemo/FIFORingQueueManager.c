//
//  FIFORingQueueManager.c
//  NVSDK
//
//  Created by Macrovideo on 2018/7/26.
//  Copyright © 2018年 macrovideo. All rights reserved.
//

#include "FIFORingQueueManager.h"

#define RING_QUEUE_LEVEL0_BUFFER_SIZE 1024*1024*5 //5M
#define RING_QUEUE_LEVEL1_BUFFER_SIZE 1024*1024*10 //10M
#define RING_QUEUE_LEVEL2_BUFFER_SIZE 1024*1024*20 //20M
#define RING_QUEUE_LEVEL3_BUFFER_SIZE 1024*1024*40 //40M
#define RING_QUEUE_LEVEL4_BUFFER_SIZE 1024*1024*60 //60M
#define RING_QUEUE_LEVEL5_BUFFER_SIZE 1024*1024*80 //80M
#define RING_QUEUE_LEVEL6_BUFFER_SIZE 1024*1024*100 //100M
#define RING_QUEUE_LEVEL7_BUFFER_SIZE 1024*1024*120 //120M

#import "DefineVars.h"
#import "Defines.h"
////
PBUFFER_MANAGER initBuffer(int nLevel);
bool releaseBuffer(PBUFFER_MANAGER bufferManager);

bool resetBuffer(PBUFFER_MANAGER bufferManager);

int64_t saveBuffer(PBUFFER_MANAGER bufferManager, char *pData, const int64_t nSize);
int64_t getBuffer(PBUFFER_MANAGER bufferManager, char *pData, int64_t nIndex, const int64_t nSize);
int64_t checkBufferSize(PBUFFER_MANAGER bufferManager);
////////

PFIFO_RING_QUEUE initRingQueue(int nLevel, int nQueueSize){
    PFIFO_RING_QUEUE ringQueue = malloc(sizeof(FIFO_RING_QUEUE));
    //init queue manager
 
//    nQueueSize = 2;
    
    if(ringQueue == NULL)
    {
        //printf("InitAudioQueue error\n");
        return NULL;
    }
    
    memset(ringQueue,0,sizeof(FIFO_RING_QUEUE));
    ringQueue->nQueueSize = nQueueSize;
    ringQueue->nFront=0;
    ringQueue->nRear=ringQueue->nFront;
    
    //init queue
    ringQueue->queue = (PRING_NODE *)malloc(sizeof(PRING_NODE)*nQueueSize);
    if(ringQueue->queue == NULL)
    {
        //printf("InitAudioQueue array error\n");
        free(ringQueue);
        ringQueue=NULL;
        return NULL;
    }
    
    //init queue data
    bool isInitSucceed=true;
    int i=0, initSize=0;
    for (i=0;i < nQueueSize; i++)
    {
        ringQueue->queue[i] = (PRING_NODE)malloc(sizeof(RING_NODE));
        if(ringQueue->queue[i] == NULL)
        {
            //printf("InitAudioQueue init queue i error\n");
            isInitSucceed=false;
            break;
        }
        initSize++;
    }
    
    //init buffer
    if(isInitSucceed==false){//init queue fail
        //xie yongsheng 20190107bug 此处有内存泄露 没有释放前面申请的两堆内存(ringQueue和里面的queue)
        //printf("InitAudioQueue init fail\n");
        if (ringQueue) {
            if (ringQueue->queue) {
                for (int i = 0; i < initSize; i++) {
                    if (ringQueue->queue[i]) {
                        free(ringQueue->queue[i]);
                        ringQueue->queue[i] = NULL;
                    } else {
                        break;
                    }
                }
                
                free(ringQueue->queue);
                ringQueue->queue = NULL;
            }
            free(ringQueue);
            ringQueue = NULL;
        }
        return NULL;
    }
    ringQueue->bufferManager = initBuffer(nLevel);
    if (ringQueue->bufferManager == NULL) {
        releaseRingQueue(ringQueue);
        ringQueue = NULL;
    }
     return ringQueue;
}
bool releaseRingQueue(PFIFO_RING_QUEUE ringQueue){
    
    printf("getBuffer releaseRingQueue******************************************\n");
    bool nResult = true;
    if (ringQueue) {
        
        //free buffer
        if (ringQueue->bufferManager) {
            releaseBuffer(ringQueue->bufferManager);
            ringQueue->bufferManager = NULL;
        }
        
        
        //free queue data
        if (ringQueue->queue) {
            int i=0, initSize = ringQueue->nQueueSize;
            for (i=0;i < initSize;i++)
            {
                
                if(ringQueue->queue[i])
                {
                    free(ringQueue->queue[i]);
                    ringQueue->queue[i] = NULL;
                }
 
            }
            
            free(ringQueue->queue);
            ringQueue->queue = NULL;
        }
  
        //free ringQueue
        free(ringQueue);
        ringQueue = NULL;
    }
    return nResult;
}

bool resetRingQueue(PFIFO_RING_QUEUE ringQueue){
    
//    printf("getBuffer resetRingQueue <<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");
    
    bool nResult = true;
    if (ringQueue) {
        resetBuffer(ringQueue->bufferManager);
        
//        printf("getBuffer resetRingQueue <<<<<<<<<<<<<<RRRR<<<<<<<<<<<<<< \n");
        ringQueue->nFront = 0;
        ringQueue->nRear = ringQueue->nFront;
        ringQueue->nWidth = 0;
        ringQueue->nHeight = 0;
        
    }
   
    return nResult;
}

bool isRingQueueEmpty(PFIFO_RING_QUEUE ringQueue){
    if(ringQueue == NULL) return true;
    
    bool bReslut = false;
    if((ringQueue -> nFront) == (ringQueue -> nRear))
    {
        bReslut = true;
    }
    return bReslut;
}

bool setParamTORingQueue(PFIFO_RING_QUEUE ringQueue, int nWidth, int nHeight){
    if (ringQueue) {
        ringQueue->nWidth = nWidth;
        ringQueue->nHeight = nHeight;
         return true;
    }
    return false;
}

int getRingQueueSize(PFIFO_RING_QUEUE ringQueue){
    int nSize;
    if (ringQueue==NULL) return -1;
    
    if((ringQueue->nFront) == (ringQueue->nRear)) {
        nSize = 0;
    } else if((ringQueue->nRear) > (ringQueue->nFront)) {
        nSize = (ringQueue->nRear) - (ringQueue->nFront);
    } else {
        nSize = (ringQueue->nQueueSize) - (ringQueue->nFront) + (ringQueue->nRear);
    }
    return nSize;
}

/**
 检查存储在队列中的数据大小
 */
int64_t getRingQueueDataSize(PFIFO_RING_QUEUE ringQueue) {
    
    if(ringQueue==NULL) {
        return RESULT_QUEUE_OP_PARAM_ERR;
    }
    
    if(ringQueue->nFront == ringQueue->nRear) {
        return 0;
    }
    
    return checkBufferSize(ringQueue->bufferManager);
}
  

int getMediaTypeFromQueue(PFIFO_RING_QUEUE ringQueue) {
    if(ringQueue==NULL){
        return RESULT_QUEUE_OP_PARAM_ERR;
    }
    
    if(ringQueue->nFront == ringQueue->nRear){
        return RESULT_QUEUE_OP_EMPTY;
    }
    
    return ringQueue->queue[ringQueue->nFront]->nMediaType;
}

int64_t getTimestampFromQueue(PFIFO_RING_QUEUE ringQueue) {
    if(ringQueue==NULL){
        return RESULT_QUEUE_OP_PARAM_ERR;
    }
    
    if(ringQueue->nFront == ringQueue->nRear){
        return RESULT_QUEUE_OP_EMPTY;
    }
    
    return ringQueue->queue[ringQueue->nFront]->lTimestamp;
}


int getTypeFromQueue(PFIFO_RING_QUEUE ringQueue){
    int nDataType = 0;
    if(ringQueue==NULL){
        return RESULT_QUEUE_OP_PARAM_ERR;
    }
    
    if(ringQueue->nFront == ringQueue->nRear){
        return RESULT_QUEUE_OP_EMPTY;
    }
    
    int nType = ringQueue->queue[ringQueue->nFront]->nType;
    
    if(nType==FRAMETYPE_I || nType==FRAMETYPE_P || nType==FRAMETYPE_H264_TIME_I || nType==FRAMETYPE_H264_TIME_P)
    {
        nDataType = NV_CODEC_ID_H264;
    }
    else if(nType==FRAMETYPE_MPEG4_I || nType==FRAMETYPE_MPEG4_P)
    {
        nDataType = NV_CODEC_ID_MPEG4;
    }
    else if(nType==FRAMETYPE_JPEG)
    {
        nDataType = NV_CODEC_ID_MJPEG;
    }else if(nType == FRAMETYPE_H265_I || nType == FRAMETYPE_H265_P || FRAMETYPE_H265_TIME_I==nType || FRAMETYPE_H265_TIME_P==nType)
    {
        nDataType = NV_CODEC_ID_H265;
    }
    // add by GWX 2020.09.14
    else if(nType == FRAMETYPE_JPEG){
        nDataType = NV_CODEC_ID_MJPEG;
    }
    else{
    }
    // end add by GWX 2020.09.14
    return nDataType;
}

int putFrameToQueue(PFIFO_RING_QUEUE ringQueue, PHSFRAME_DATA pFrameData){
    int nResult = RESULT_QUEUE_OP_PARAM_ERR;
    
    if(ringQueue==NULL || ringQueue->queue==NULL || pFrameData == NULL ){
        return RESULT_QUEUE_OP_PARAM_ERR;
    }
   
//    printf("putDataToQueue: %d, %d, %d\n", ringQueue->nRear, ringQueue->nQueueSize, ringQueue->nFront);
    //check if queue is full
    if((ringQueue->nRear + 1)% (ringQueue->nQueueSize) == ringQueue->nFront) {
        return RESULT_QUEUE_OP_FULL;
    }
    
    //save data to buffer
    int64_t nIndex = saveBuffer(ringQueue->bufferManager, pFrameData->data, pFrameData->nSize);

//    printf("putFrameToQueue: --lTimestamp =%lld \n",  pFrameData->timestamp);
    
    if (nIndex >= 0 ) {
        ringQueue->queue[ringQueue->nRear]->nId = pFrameData->fId;
        ringQueue->queue[ringQueue->nRear]->nMediaType = pFrameData->mediaType;
        ringQueue->queue[ringQueue->nRear]->nType = pFrameData->nType;
        ringQueue->queue[ringQueue->nRear]->nSize = pFrameData->nSize;
        ringQueue->queue[ringQueue->nRear]->lTimestamp = pFrameData->timestamp;
        ringQueue->queue[ringQueue->nRear]->nIndex = nIndex;
        ringQueue->queue[ringQueue->nRear]->nFlag = pFrameData->flag;
        ringQueue->queue[ringQueue->nRear]->nFrameRate = 0;
        ringQueue->queue[ringQueue->nRear]->nWidth = pFrameData->width;
        ringQueue->queue[ringQueue->nRear]->nHeight = pFrameData->height;
        
        ringQueue->nRear = (ringQueue->nRear+1) % (ringQueue->nQueueSize);
        
        
        nResult = RESULT_QUEUE_OP_OK;
    }else{
        return RESULT_QUEUE_OP_NO_BUFFER;
    }
 
    return nResult;
}

  
int getFrameFromQueue(PFIFO_RING_QUEUE ringQueue, PHSFRAME_DATA pFrameData){
    
    
    if(ringQueue==NULL || pFrameData == NULL)
    {
        return RESULT_QUEUE_OP_PARAM_ERR;
    }
    
    if(ringQueue->nFront == ringQueue->nRear)//
    {
        return RESULT_QUEUE_OP_EMPTY;
    }

//    printf("getDataFromQueue: ** %lld, %lld, %lld\n", ringQueue->nRear, ringQueue->nQueueSize, ringQueue->nFront);
    
    //get data from buffer manager
    int64_t nSize =  getBuffer(ringQueue->bufferManager, pFrameData->data, ringQueue->queue[ringQueue->nFront]->nIndex, ringQueue->queue[ringQueue->nFront]->nSize);
    
 
    if (nSize != ringQueue->queue[ringQueue->nFront]->nSize) {
        
        return RESULT_QUEUE_SIZE_ERR;
    }
 
//    printf("getDataFromQueue: --lTimestamp =%lld \n",  ringQueue->queue[ringQueue->nFront]->lTimestamp);
    
    pFrameData->fId = ringQueue->queue[ringQueue->nFront]->nId;
    pFrameData->mediaType = ringQueue->queue[ringQueue->nFront]->nMediaType;
    pFrameData->nType = ringQueue->queue[ringQueue->nFront]->nType;
    pFrameData->nSize = ringQueue->queue[ringQueue->nFront]->nSize;
    pFrameData->flag = ringQueue->queue[ringQueue->nFront]->nFlag;
//    pFrameData-> = ringQueue->queue[ringQueue->nFront]->nFrameRate;
    pFrameData->width = ringQueue->queue[ringQueue->nFront]->nWidth;
    pFrameData->height = ringQueue->queue[ringQueue->nFront]->nHeight;
    pFrameData->timestamp = ringQueue->queue[ringQueue->nFront]->lTimestamp;
    
    ringQueue->nFront = (ringQueue->nFront+1)% (ringQueue->nQueueSize);
    return (int)nSize;
}

int putDataToQueue(PFIFO_RING_QUEUE ringQueue, const char *pData,  int nSize, int nId, int nMediaType, int nType, int nFlag, int64_t lTimestamp, int nFrameRate , int width , int height){
    int nResult = RESULT_QUEUE_OP_PARAM_ERR;
    
    if(ringQueue==NULL || ringQueue->queue==NULL){
        return RESULT_QUEUE_OP_PARAM_ERR;
    }
   
//    printf("putDataToQueue: %d, %d, %d\n", ringQueue->nRear, ringQueue->nQueueSize, ringQueue->nFront);
    //check if queue is full
    if((ringQueue->nRear + 1)% (ringQueue->nQueueSize) == ringQueue->nFront) {
        return RESULT_QUEUE_OP_FULL;
    }
    
    //save data to buffer
    int64_t nIndex = saveBuffer(ringQueue->bufferManager, pData, nSize);

    if (nIndex >= 0 ) {
        ringQueue->queue[ringQueue->nRear]->nId = nId;
        ringQueue->queue[ringQueue->nRear]->nMediaType = nMediaType;
        ringQueue->queue[ringQueue->nRear]->nType = nType;
        ringQueue->queue[ringQueue->nRear]->nSize = nSize;
        ringQueue->queue[ringQueue->nRear]->lTimestamp = lTimestamp;
        ringQueue->queue[ringQueue->nRear]->nIndex = nIndex;
        ringQueue->queue[ringQueue->nRear]->nFlag = nFlag;
        ringQueue->queue[ringQueue->nRear]->nFrameRate = nFrameRate;
        ringQueue->queue[ringQueue->nRear]->nWidth = width;
        ringQueue->queue[ringQueue->nRear]->nHeight = height;
        
        ringQueue->nRear = (ringQueue->nRear+1) % (ringQueue->nQueueSize);
        
        
        nResult = RESULT_QUEUE_OP_OK;
    }else{
        return RESULT_QUEUE_OP_NO_BUFFER;
    }
 
    return nResult;
}


int getDataFromQueue(PFIFO_RING_QUEUE ringQueue, const char *pData, int mediaInfos[], int64_t lTimestamp[]){
 
  
    if(ringQueue==NULL)
    {
        return RESULT_QUEUE_OP_PARAM_ERR;
    }
    
    if(ringQueue->nFront == ringQueue->nRear)// 
    {
        return RESULT_QUEUE_OP_EMPTY;
    }

//    printf("getDataFromQueue: ** %lld, %lld, %lld\n", ringQueue->nRear, ringQueue->nQueueSize, ringQueue->nFront);
    
    //get data from buffer manager
    int64_t nSize =  getBuffer(ringQueue->bufferManager, pData, ringQueue->queue[ringQueue->nFront]->nIndex, ringQueue->queue[ringQueue->nFront]->nSize);
    
 
    if (nSize != ringQueue->queue[ringQueue->nFront]->nSize) {
        
        return RESULT_QUEUE_SIZE_ERR;
    }
 
    //printf("getDataFromQueue: --Size =%lld,  %lld, %lld\n",  ringQueue->queue[ringQueue->nFront]->nIndex, nSize, ringQueue->queue[ringQueue->nFront]->nSize);
    
    mediaInfos[0] = ringQueue->queue[ringQueue->nFront]->nId;
    mediaInfos[1] = ringQueue->queue[ringQueue->nFront]->nMediaType;
    mediaInfos[2] = ringQueue->queue[ringQueue->nFront]->nType;
    mediaInfos[3] = ringQueue->queue[ringQueue->nFront]->nSize;
    mediaInfos[4] = ringQueue->queue[ringQueue->nFront]->nFlag;
    mediaInfos[5] = ringQueue->queue[ringQueue->nFront]->nFrameRate;
    mediaInfos[6] = ringQueue->queue[ringQueue->nFront]->nWidth;
    mediaInfos[7] = ringQueue->queue[ringQueue->nFront]->nHeight;
    lTimestamp[0] = ringQueue->queue[ringQueue->nFront]->lTimestamp;
    
    ringQueue->nFront = (ringQueue->nFront+1)% (ringQueue->nQueueSize);
    return (int)nSize;
}


///
PBUFFER_MANAGER initBuffer(int nLevel){
    PBUFFER_MANAGER bufferManager =   malloc(sizeof(BUFFER_MANAGER));
    unsigned long nSize = RING_QUEUE_LEVEL0_BUFFER_SIZE;
    switch (nLevel) {
        case RING_QUEUE_LEVEL0:
            nSize = RING_QUEUE_LEVEL0_BUFFER_SIZE;
            break;
        case RING_QUEUE_LEVEL1:
            nSize = RING_QUEUE_LEVEL1_BUFFER_SIZE;
            break;
        case RING_QUEUE_LEVEL2:
            nSize = RING_QUEUE_LEVEL2_BUFFER_SIZE;
            break;
        case RING_QUEUE_LEVEL3:
            nSize = RING_QUEUE_LEVEL3_BUFFER_SIZE;
            break;
        case RING_QUEUE_LEVEL4:
            nSize = RING_QUEUE_LEVEL4_BUFFER_SIZE;
            break;
        case RING_QUEUE_LEVEL5:
            nSize = RING_QUEUE_LEVEL5_BUFFER_SIZE;
            break;
        case RING_QUEUE_LEVEL6:
            nSize = RING_QUEUE_LEVEL6_BUFFER_SIZE;
            break;
        case RING_QUEUE_LEVEL7:
            nSize = RING_QUEUE_LEVEL7_BUFFER_SIZE;
            break;
        default:
            nSize = RING_QUEUE_LEVEL0_BUFFER_SIZE;
            break;
    }
    bufferManager->buffer = malloc(sizeof(char)*nSize);;
    
    if (bufferManager->buffer == NULL) {
        free(bufferManager);
        
        return NULL;
    }
    
    bufferManager->nBufferSize = nSize;
    bufferManager->nLestSize = bufferManager->nBufferSize;
    bufferManager->nFront = 0;
    bufferManager->nRear = bufferManager->nFront;
    return bufferManager;
}

bool releaseBuffer(PBUFFER_MANAGER bufferManager){
    bool nResult = true;
    
//    printf("getBuffer releaseBuffer___________________");
    
    if (bufferManager) {
        if (bufferManager->buffer != NULL) {
            
            free(bufferManager->buffer);
            bufferManager->buffer = NULL;
            
//            printf("getBuffer releaseBuffer________free_ buffer__________");
        }
        
        free(bufferManager);
        bufferManager=NULL;
    }
    
    return nResult;
}

bool resetBuffer(PBUFFER_MANAGER bufferManager){
    bool nResult = true;
//    printf("getBuffer resetBuffer---->>>>>>>>");
    if (bufferManager) {
        bufferManager->nLestSize = bufferManager->nBufferSize;
        bufferManager->nFront = 0;
        bufferManager->nRear = bufferManager->nFront;
        if (bufferManager->buffer) {
//            printf("getBuffer resetBuffer---->>>>memset >>>>");
            memset(bufferManager->buffer, 0, bufferManager->nBufferSize);
        }
    }
    
    return nResult;
}

//将数据保存到缓存块中，并返回保存在缓存块的下标（地址）
int64_t saveBuffer(PBUFFER_MANAGER bufferManager, char *pData, const int64_t nSize){
    int64_t nIndex = -1;
    if (bufferManager == NULL || nSize <= 0) {
        return RESULT_QUEUE_OP_PARAM_ERR;
    }
    
    
    //先检查是否有足够空余的空间
    if(nSize > bufferManager->nLestSize-1){//留有一个byte的间隙，避免队列满时头尾也相连
        return RESULT_QUEUE_OP_FULL;
    }
    
    
    if (bufferManager->nFront > bufferManager->nRear) {
        //这种情况可以直接将数据拷入队列
        nIndex = bufferManager->nRear;
        memcpy(bufferManager->buffer + nIndex, pData, nSize);
        bufferManager->nRear += nSize;
          //printf("saveBuffer:A %lld, %lld, %lld, %lld\n", bufferManager->nRear, bufferManager->nFront, nSize, bufferManager->nBufferSize);
    }else{
        if(bufferManager->nBufferSize - bufferManager->nRear >= nSize){//这种情况可以直接将数据拷入队列
            
             //printf("saveBuffer:B %lld, %lld, %lld, %lld\n", bufferManager->nRear, bufferManager->nFront, nSize, bufferManager->nBufferSize);
            
            nIndex = bufferManager->nRear;
            memcpy(bufferManager->buffer + nIndex, pData, nSize);
            bufferManager->nRear += nSize;
        }else{
            //printf("saveBuffer:E0 %lld, %lld, %lld, %lld\n", bufferManager->nRear, bufferManager->nFront, nSize, bufferManager->nBufferSize);
            
            nIndex = bufferManager->nRear;
            int64_t nCopySize = bufferManager->nBufferSize - nIndex;
            memcpy(bufferManager->buffer + nIndex, pData, nCopySize);
            
            //printf("saveBuffer:E1 %lld, %lld, %lld, %lld\n", bufferManager->nRear, bufferManager->nFront, nCopySize, bufferManager->nBufferSize);
            
            bufferManager->nRear = nSize - nCopySize;
            memcpy(bufferManager->buffer, pData+nCopySize, bufferManager->nRear);
            
            //printf("saveBuffer:E2 %lld, %lld, %lld, %lld\n", bufferManager->nRear, bufferManager->nFront,   bufferManager->nBufferSize);
        }
    }
    
    if (bufferManager->nFront == bufferManager->nBufferSize) {// 指针到了buffer的末端，将其置为开始段
        bufferManager->nFront = 0;
    }
    
    if (bufferManager->nRear == bufferManager->nBufferSize) {// 指针到了buffer的末端，将其置为开始段
        bufferManager->nRear = 0;
    }
    bufferManager->nLestSize -= nSize;
    return nIndex;
}

//根据下标和大小，从缓存块中取出数据
int64_t getBuffer(PBUFFER_MANAGER bufferManager, char *pData, int64_t nIndex, const int64_t nSize){
      if (bufferManager == NULL || bufferManager->buffer==NULL) {
        return RESULT_QUEUE_OP_PARAM_ERR;
    }

    //
     if (nSize > bufferManager->nBufferSize - bufferManager->nLestSize || nIndex != bufferManager->nFront) {
        return RESULT_QUEUE_OP_PARAM_ERR;
    }
 
  
//    printf("getBuffer %lld, %lld, %lld- %lld =%lld \n", bufferManager->nFront , bufferManager->nRear, bufferManager->nBufferSize, bufferManager->nLestSize, bufferManager->nBufferSize - bufferManager->nLestSize);
    if (bufferManager->nFront < bufferManager->nRear) {

// printf("getBuffer (%d, %d) %lld, %lld, %lld- %lld =%lld \n",bufferManager->buffer, nIndex, bufferManager->nFront , bufferManager->nRear, bufferManager->nBufferSize, bufferManager->nLestSize, bufferManager->nBufferSize - bufferManager->nLestSize);
 
        
        memcpy(pData, bufferManager->buffer + bufferManager->nFront, nSize);
        bufferManager->nFront += nSize;
    }else{
        if (bufferManager->nBufferSize - bufferManager->nFront >= nSize) {
            memcpy(pData, bufferManager->buffer + bufferManager->nFront, nSize);
            bufferManager->nFront += nSize;
           
        }else{
            int64_t nCopySize = bufferManager->nBufferSize - bufferManager->nFront;
            memcpy(pData, bufferManager->buffer + bufferManager->nFront, nCopySize);
            bufferManager->nFront = nSize - nCopySize;
            memcpy(pData+nCopySize, bufferManager->buffer,  bufferManager->nFront);
        }
        
    }

    if (bufferManager->nFront == bufferManager->nBufferSize) {// 指针到了buffer的末端，将其置为开始段
        bufferManager->nFront = 0;
    }
    
    if (bufferManager->nRear == bufferManager->nBufferSize) {// 指针到了buffer的末端，将其置为开始段
        bufferManager->nRear = 0;
    }
    bufferManager->nLestSize += nSize;
    return nSize;
}

int64_t checkBufferSize(PBUFFER_MANAGER bufferManager) {
    if (bufferManager == NULL || bufferManager->buffer==NULL) {
        return RESULT_QUEUE_OP_PARAM_ERR;
    }
    
    return bufferManager->nBufferSize - bufferManager->nLestSize;
}
