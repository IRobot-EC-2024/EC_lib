/**
 * @Author       : H0pefu12 573341043@qq.com
 * @Date         : 2024-03-26 00:36:24
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-08 13:48:38
 * @Description  :
 * @Filename     : uart_dma_double.h
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#ifndef __UART_DMA_DOUBLE_H
#define __UART_DMA_DOUBLE_H

#include "struct_typedef.h"
#include "usart.h"

HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_DMA_double(UART_HandleTypeDef* huart,
                                                      uint8_t* pData,
                                                      uint8_t* pData1,
                                                      uint16_t Size);

#endif