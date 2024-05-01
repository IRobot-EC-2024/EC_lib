/**
 * @Author       : Specific-Cola specificcola@proton.me
 * @Date         : 2024-04-07 00:48:03
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-17 02:37:47
 * @Description  :
 * @Filename     : bsp_can.h
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#ifndef BSP_CAN_H__
#define BSP_CAN_H__

#include "bsp_monitor/bsp_monitor.h"
#include "struct_typedef.h"

#if defined(STM32F407xx) || defined(STM32F427xx)
#define CAN_DEVICE
#define CAN_HANDLE1 hcan1
#define CAN_HANDLE2 hcan2
#elif defined(STM32H723xx)
#define FDCAN_DEVICE
#define CAN_HANDLE1 hfdcan1
#define CAN_HANDLE2 hfdcan2
#define CAN_HANDLE3 hfdcan3
#endif

#ifdef HAL_CAN_MODULE_ENABLED
#include "can.h"
typedef CAN_HandleTypeDef Can_Handle_t;
#elif defined(HAL_FDCAN_MODULE_ENABLED)
#include "fdcan.h"
typedef FDCAN_HandleTypeDef Can_Handle_t;
#endif

#define CAN_MX_REGISTER_CNT 40

typedef struct Can_Device_ {
    State_t state;  // 设备状态

#ifdef CAN_DEVICE
    CAN_HandleTypeDef* can_handle;  // can句柄
    CAN_TxHeaderTypeDef tx_config;  // CAN报文发送配置
#elif defined(FDCAN_DEVICE)
    FDCAN_HandleTypeDef* can_handle;  // fdcan句柄
    FDCAN_TxHeaderTypeDef tx_config;  // fdcan报文发送配置
#endif
    uint32_t tx_id;       // 发送id
    uint32_t tx_mailbox;  // CAN消息填入的邮箱号
    uint8_t tx_buff[8];   // 发送缓存
    uint32_t rx_id;       // 接收id
    uint8_t rx_buff[8];   // 接收缓存,最大消息长度为8
    uint8_t rx_len;       // 接收长度,可能为0-8

    // 接收的回调函数,用于解析接收到的数据
    void (*can_device_callback)(struct Can_Device_*);
    // 离线回调处理
    void (*can_device_offline_callback)(struct Can_Device_*);

    void* parent;  // 父对象,用于回调函数中使用

    Monitor_Device_t* monitor_handle;  // 监测器

} Can_Device_t;

typedef struct {
#ifdef CAN_DEVICE
    CAN_HandleTypeDef* can_handle;  // can句柄
#elif defined(FDCAN_DEVICE)
    FDCAN_HandleTypeDef* can_handle;  // fdcan句柄
#endif
    uint32_t tx_id;  // 发送id
    uint32_t rx_id;  // 接收id
    uint8_t tx_dlc;
    uint16_t offline_threshold;                  // 单位ms
    void (*can_device_callback)(Can_Device_t*);  // 处理接收数据的回调函数
    void (*can_device_offline_callback)(Can_Device_t*);

    void* parent;  // 父对象,用于回调函数中使用
} Can_Register_t;

extern void canFilterConfig(Can_Device_t* device);
Can_Device_t* canDeviceRegister(Can_Register_t* reg);
extern void canOnInit(void);
extern void canOnActivate(void);
extern void canOnDeactivate(void);
extern Return_t canSendMessage(Can_Device_t* instance, uint8_t* message);

#endif  // BSP_CAN_H