/**
 * @Author       : Specific-Cola specificcola@proton.me
 * @Date         : 2024-04-08 12:12:57
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-08 14:53:22
 * @Description  :
 * @Filename     : bsp_usart.c
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#include "bsp_usart.h"

#include <stdlib.h>
#include <string.h>

#include "uart_dma_double.h"

#if defined(STM32H723xx)
#define DMA_GET_DBM(hdma)                                                    \
    ((hdma) != 0                                                             \
         ? (((DMA_Stream_TypeDef*)hdma->Instance)->CR & DMA_SxCR_CIRC) != 0  \
         : (((BDMA_Channel_TypeDef*)hdma->Instance)->CCR & BDMA_CCR_CIRC) != \
               0)
#elif defined(STM32F427xx) || defined(STM32F407xx)
#define DMA_GET_DBM(hdma) \
    ((((DMA_Stream_TypeDef*)hdma->Instance)->CR & DMA_SxCR_CIRC) != 0)

#endif
static Usart_Device_t* usart_device[USART_MX_REGISTER_CNT] = {NULL};
static uint8_t id_cnt = 0;  // 全局USART实例索引,每次有新的模块注册会自增

static void usartDMARestart(Usart_Device_t* instance) {
    switch (instance->rx_buff_num) {
        case 1:
            HAL_UARTEx_ReceiveToIdle_DMA(instance->usart_handle,
                                         instance->rx_buff, instance->rx_len);
            __HAL_DMA_DISABLE_IT(instance->usart_handle->hdmarx, DMA_IT_HT);
            break;
        case 2:
            HAL_UARTEx_ReceiveToIdle_DMA_double(
                instance->usart_handle, instance->rx_buff2[0],
                instance->rx_buff2[1], instance->rx_len);
            __HAL_DMA_DISABLE_IT(instance->usart_handle->hdmarx, DMA_IT_HT);
            break;
        default:
            break;
    }
}

static void usartStartReceive(Usart_Device_t* instance) {
    if (instance == NULL) {
        return;
    }

    if (instance->rx_buff_num == 1) {
        // 单缓冲区
        HAL_UARTEx_ReceiveToIdle_DMA(instance->usart_handle, instance->rx_buff,
                                     instance->rx_len);
        __HAL_DMA_DISABLE_IT(instance->usart_handle->hdmarx, DMA_IT_HT);
    } else if (instance->rx_buff_num == 2) {
        // 双缓冲区
        HAL_UARTEx_ReceiveToIdle_DMA_double(
            instance->usart_handle, instance->rx_buff2[0],
            instance->rx_buff2[1], instance->rx_len);
        __HAL_DMA_DISABLE_IT(instance->usart_handle->hdmarx, DMA_IT_HT);
    } else {
        Error_Handler();
    }
}

static void usartOfflineCallback(Monitor_Device_t* monitor) {
    if (monitor == NULL || monitor->device == NULL) return;
    Usart_Device_t* instance = (Usart_Device_t*)monitor->device;
    instance->state = STATE_OFFLINE;
    if (instance->usart_device_offline_callback != NULL) {
        instance->usart_device_offline_callback(instance);
    }
}

Usart_Device_t* usartDeviceRegister(Usart_Register_t* reg) {
    if (id_cnt > USART_MX_REGISTER_CNT) {
        Error_Handler();  // 后面希望定义一个全局变量来展示错误类型
    }

    for (uint8_t i = 0; i < id_cnt; i++) {
        if (usart_device[i]->usart_handle == reg->usart_handle) {
            Error_Handler();
        }
    }

    Usart_Device_t* instance = (Usart_Device_t*)malloc(sizeof(Usart_Device_t));

    if (reg->rx_buff_num > 2) {
        reg->rx_buff_num = 2;
    }
    if (reg->rx_buff_num < 1) {
        reg->rx_buff_num = 1;
    }

    instance->usart_handle = reg->usart_handle;
    instance->rx_len = reg->rx_len;
    instance->rx_buff_num = reg->rx_buff_num;
    instance->usart_device_callback = reg->usart_device_callback;

    Monitor_Register_t monitor_reg;

    monitor_reg.device = instance;
    monitor_reg.offlineCallback = usartOfflineCallback;
    monitor_reg.offline_threshold = reg->offline_threshold;
    instance->monitor_handle = monitorInit(&monitor_reg);

    instance->state = STATE_ONLINE;
    usart_device[id_cnt++] = instance;  // 完成自增

    usartStartReceive(instance);  // 注册完成后直接开启接收

    return instance;
}

void usartOnDeactivate(void);

Return_t usartSendMessage(Usart_Device_t* instance, uint8_t* message,
                          uint16_t tx_len, Usart_Transfer_Mode mode) {
    Return_t ret;

    switch (mode) {
        case USART_TRANSFER_DMA:
            if (HAL_UART_Transmit_DMA(instance->usart_handle, message,
                                      tx_len) != HAL_OK) {
                ret = RETURN_ERROR;
            }
            break;

        case USART_TRANSFER_IT:
            if (HAL_UART_Transmit_IT(instance->usart_handle, message, tx_len) !=
                HAL_OK) {
                ret = RETURN_ERROR;
            }
            break;

        case USART_TRANSFER_BLOCKING:
            if (HAL_UART_Transmit(instance->usart_handle, message, tx_len,
                                  0xFF) != HAL_OK) {
                ret = RETURN_ERROR;
            }
            break;

        case USART_TRANSFER_NONE:
            break;
        default:
            break;
    }
    return ret;
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart,
                                uint16_t size)  // todo  双缓存区如何接收
{
    // find the instance which is being handled
    for (uint8_t i = 0; i < id_cnt; ++i) {
        // call the callback function
        if (huart == usart_device[i]->usart_handle) {
            // if it is not NULL
            if (usart_device[i]->rx_buff_num == 2) {
                usart_device[i]->rx_info.rx_buff_select =
                    DMA_GET_DBM(usart_device[i]->usart_handle->hdmarx);
                usartDMARestart(usart_device[i]);
                // 双缓冲区可以重使能DMA，再处理回调
                if (usart_device[i]->usart_device_callback != NULL) {
                    usart_device[i]->rx_info.this_time_rx_len = size;
                    usart_device[i]->usart_device_callback(usart_device[i]);
                    memset(usart_device[i]->rx_buff, 0,
                           size);  // 接收结束后清空buffer,对于变长数据是必要的
                                   // 如果需要清除，就在回调函数里清除
                }
            } else {
                if (usart_device[i]->usart_device_callback != NULL) {
                    usart_device[i]->rx_info.this_time_rx_len = size;
                    usart_device[i]->usart_device_callback(usart_device[i]);
                    // 接收结束后清空buffer,对于变长数据是必要的
                    memset(usart_device[i]->rx_buff, 0, size);
                    // 如果需要清除，就在回调函数里清除
                }
                usartDMARestart(usart_device[i]);
            }
            return;  // break the loop
        }
    }
}

uint64_t PE_cnt = 0;
uint64_t FE_cnt = 0;

void HAL_UART_ErrorCallback(UART_HandleTypeDef* huart) {
    for (uint8_t i = 0; i < id_cnt; ++i) {
        if (huart == usart_device[i]->usart_handle) {
            usartDMARestart(usart_device[i]);
            return;
        }
    }
}
// 定义几种串口常用的工作模式，进行配置，例如串口空闲中断
