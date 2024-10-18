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

#include "era_types.h"
#include "uart.h"
#include "databuffer.h"

extern uint8_t diff_recv_buffer[DIFFDATA_RECV_LEN];

extern DiffDataBuffer diffDataBuffer;

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;



static void printInfo(char* info) 
{
    char strCount[32];
    //sprintf(strCount, "%d, %d, %d ", imu_frame_count, ksxt_frame_count, gga_frame_count);
	char strResult[128];
	strcpy(strResult, strCount);
	strcat(strResult, info);

    HAL_UART_Transmit_DMA(&huart1, (uint8_t*)strResult, strlen(strResult));
}

int uart3_free_to_send = 1;
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

    if (huart == &huart3) {
        uart3_free_to_send = 1;
    }
}

void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart4) {
        uint8_t* pRecvData;
        int len = era_get_recv_buffer((uint8_t*)&diffDataBuffer, &pRecvData);
        memcpy(pRecvData, diff_recv_buffer, DIFFDATA_RECV_LEN/2);
        era_rx_complete((uint8_t*)&diffDataBuffer);
    }
 }

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart4) {
        uint8_t* pRecvData;
        int len = era_get_recv_buffer((uint8_t*)&diffDataBuffer, &pRecvData);
        memcpy(pRecvData, diff_recv_buffer + DIFFDATA_RECV_LEN/2, DIFFDATA_RECV_LEN/2);
        era_rx_complete((uint8_t*)&diffDataBuffer);
    }
}

void init_data_buffer()
{
    era_init_buffer(DIFFDATA_ITEM_NUM, DIFFDATA_ITEM_LEN, (uint8_t*)&diffDataBuffer);
}

void uart4_start_recv()
{
    HAL_UART_Receive_DMA(&huart4, diff_recv_buffer, DIFFDATA_RECV_LEN);
}



void uart3_check_send()
{
    if (uart3_free_to_send) {
        uint8_t* pSendData;
        int len = era_get_send_buffer((uint8_t*)&diffDataBuffer, &pSendData);
		if (len != 0) {
			uart3_free_to_send = 0;
			HAL_UART_Transmit_DMA(&huart3, pSendData, len);
		}
    }
}