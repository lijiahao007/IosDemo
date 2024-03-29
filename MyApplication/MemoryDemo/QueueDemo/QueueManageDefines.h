//
//  QueueManageDefines.h
//  NVSDK
//
//  Created by Macrovideo on 2018/12/6.
//  Copyright © 2018 macrovideo. All rights reserved.
//

#ifndef QueueManageDefines_h
#define QueueManageDefines_h

#define FRAME_DATA_SIZE 1024*1024    // Maximum frame size
#define YUV_FRAME_DATA_SIZE 2560*1920*3/2    // Maximum frame size
#define THERMAL_FRAME_DATA_SIZE 320*240*3    // Maximum frame size


#define RING_QUEUE_LEVEL0 0
#define RING_QUEUE_LEVEL1 1
#define RING_QUEUE_LEVEL2 2
#define RING_QUEUE_LEVEL3 3
#define RING_QUEUE_LEVEL4 4
#define RING_QUEUE_LEVEL5 5
#define RING_QUEUE_LEVEL6 6
#define RING_QUEUE_LEVEL7 7

#define RESULT_QUEUE_OP_OK 1
#define RESULT_QUEUE_OP_EMPTY 0

#define RESULT_QUEUE_OP_FULL -1
#define RESULT_QUEUE_OP_PARAM_ERR -2
#define RESULT_QUEUE_SIZE_ERR -3
#define RESULT_QUEUE_OP_NO_BUFFER -4

#define MEDIA_TYPE_MSG 0
#define MEDIA_TYPE_VIDEO 1
#define MEDIA_TYPE_AUDIO 2

#endif /* QueueManageDefines_h */
