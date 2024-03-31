//=====================================================================================================
// bsp_uart.c
//=====================================================================================================
//
//       IRobot  EC_lib
//
// GitHub: https://github.com/Hopefu12
// Date			Author			Notes
//
//
//=====================================================================================================

#ifndef __UART_DMA_DOUBLE_H
#define __UART_DMA_DOUBLE_H

#include "struct_typedef.h"
#include "usart.h"

HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_DMA_double(UART_HandleTypeDef *huart, uint8_t *pData, uint8_t *pData1, uint16_t Size);

#endif