/**
 * @Author       : Specific_Cola specificcola@proton.me
 * @Date         : 2024-03-22 23:57:28
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-11 00:25:02
 * @Description  :
 * @Filename     : bsp_usart.h
 * @
 */
#ifndef BSP_USART_H__
#define BSP_USART_H__

#include "bsp_monitor/bsp_monitor.h"
#include "hal_config.h"
#include "struct_typedef.h"
#include "usart.h"

#define USART_MX_REGISTER_CNT 3
#define USART_RXBUFF_LIMIT 256  // 如果协议需要更大的buff,请修改这里

/* 发送模式枚举 */
typedef enum {
    USART_TRANSFER_NONE = 0,
    USART_TRANSFER_BLOCKING,
    USART_TRANSFER_IT,
    USART_TRANSFER_DMA,
} Usart_Transfer_Mode;

typedef struct {
    uint8_t rx_buff_select;
    uint16_t this_time_rx_len;
} Usart_Receive_Info_t;

typedef struct Usart_Device_ {
    uint8_t state;
    UART_HandleTypeDef* usart_handle;  // uart句柄

    uint8_t* rx_buff;     // 单缓冲区使用
    uint8_t* rx_buff2;    // 双缓存区使用
    uint16_t rx_len;      // 接收一包数据的大小
    uint8_t rx_buff_num;  // 缓存区数目
    Usart_Receive_Info_t rx_info;
    // 接收的回调函数,用于解析接收到的数据
    void (*usart_device_callback)(struct Usart_Device_*);

    // 离线回调处理
    void (*usart_device_offline_callback)(struct Usart_Device_*);

    void* parent;  // 父对象,用于回调函数中使用

    Monitor_Device_t* monitor_handle;  // 监测器

} Usart_Device_t;

typedef struct {
    UART_HandleTypeDef* usart_handle;  // uart句柄

    uint16_t rx_len;      // 接收一包数据的大小
    uint8_t rx_buff_num;  // 缓存区数目
    // 接收回调函数
    void (*usart_device_callback)(Usart_Device_t*);
    // 离线回调处理
    void (*usart_device_offline_callback)(Usart_Device_t*);
    void* parent;  // 父对象,用于回调函数中使用
    uint32_t offline_threshold;

} Usart_Register_t;

extern Usart_Device_t* usartDeviceRegister(Usart_Register_t* reg);
extern Return_t usartSendMessage(Usart_Device_t* instance, uint8_t* message,
                                 uint16_t tx_len, Usart_Transfer_Mode mode);

#endif