/*********************************************************************
 *
 *  This file is part of the [OPEN_MICRO_MOWER_BASE] project.
 *  Licensed under the MIT License for non-commercial purposes.
 *  Author: Brook Li
 *  Email: lguitech@126.com
 *
 *  For more details, refer to the LICENSE file or contact [lguitech@126.com].
 *
 *  Commercial use requires a separate license.
 *
 *  This software is provided "as is", without warranty of any kind.
 *
 *********************************************************************/

#ifndef __ERA_TYPE_H__
#define __ERA_TYPE_H__

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stm32f4xx_hal.h"


#define DIFFDATA_RECV_LEN 1024

#define DIFFDATA_ITEM_NUM 4
#define DIFFDATA_ITEM_LEN 512
typedef struct _DiffDataBuffer {
    int item_num;
    int item_len;
    int pos_head;
    int pos_tail;
    uint8_t buffer[DIFFDATA_ITEM_NUM * DIFFDATA_ITEM_LEN];
} DiffDataBuffer;


#endif
