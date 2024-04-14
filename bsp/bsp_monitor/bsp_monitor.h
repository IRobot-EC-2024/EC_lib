/**
 * @Author       : H0pefu12 573341043@qq.com
 * @Date         : 2024-04-07 00:48:03
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-15 02:04:49
 * @Description  :
 * @Filename     : bsp_monitor.h
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#ifndef BSP_MONITOR_H__
#define BSP_MONITOR_H__

#include "struct_typedef.h"

#define MONITOR_DEVICE_NUM 20

typedef enum {
    MONITOR_DEVICE_ONLINE = 0,
    MONITOR_DEVICE_OFFLINE = 1,
} Monitor_Device_Status;

typedef struct Monitor_Device_ {
    uint32_t offline_counter;            // 离线计数器，单位ms
    uint32_t offline_threshold;          // 离线计数阈值，单位ms
    Monitor_Device_Status offline_flag;  // 离线标志

    void (*offlineCallback)(struct Monitor_Device_*);

    void* device;  // 监视设备地址

} Monitor_Device_t;

typedef struct {
    uint32_t offline_threshold;  // 离线计数阈值，单位ms
    void (*offlineCallback)(struct Monitor_Device_*);
    void* device;
} Monitor_Register_t;

Monitor_Device_t* monitorInit(Monitor_Register_t* monitor_reg);
void monitorRefresh(Monitor_Device_t* monitor_device);

// 计时及状态更新
Monitor_Device_Status monitorCounter(Monitor_Device_t* monitor_device);
void monitorCounterAll(void);

#endif