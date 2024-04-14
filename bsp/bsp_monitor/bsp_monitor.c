/**
 * @Author       : H0pefu12 573341043@qq.com
 * @Date         : 2024-04-02 19:10:02
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-15 02:04:34
 * @Description  :
 * @Filename     : bsp_monitor.c
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#include "bsp_monitor.h"

#include <stdlib.h>
#include <string.h>

static Monitor_Device_t* monitor_devices[MONITOR_DEVICE_NUM] = {NULL};
static uint8_t id_cnt = 0;  // 全局CAN实例索引,每次有新的模块注册会自增

/**
 * @description: 注册监视器，用以检测设备
 * @param {Monitor_Register_t*} monitor_reg
 * @return {*}
 */
Monitor_Device_t* monitorInit(Monitor_Register_t* monitor_reg) {
    Monitor_Device_t* monitor_device = (Monitor_Device_t*)malloc(sizeof(Monitor_Device_t));

    memset(monitor_device, 0, sizeof(Monitor_Device_t));
    monitor_device->device = monitor_reg->device;
    monitor_device->offline_threshold = monitor_reg->offline_threshold;
    monitor_device->offlineCallback = monitor_reg->offlineCallback;
    monitor_device->offline_counter = 0;
    monitor_device->offline_flag = MONITOR_DEVICE_ONLINE;

    monitor_devices[id_cnt] = monitor_device;
    id_cnt++;
    return monitor_device;
}

/**
 * @description: 设备正常工作时，调用此函数更新监视器
 * @param {Monitor_Device_t*} monitor_device
 * @return {*}
 */
void monitorRefresh(Monitor_Device_t* monitor_device) {
    if (monitor_device == NULL) {
        return;
    }
    monitor_device->offline_counter = 0;
    monitor_device->offline_flag = MONITOR_DEVICE_ONLINE;
}

/**
 * @description: 监视器离线计数器自增，检测设备是否离线
 * @param {Monitor_Device_t*} monitor_device
 * @return {*}
 */
Monitor_Device_Status monitorCounter(Monitor_Device_t* monitor_device) {
    if (monitor_device == NULL) {
        return MONITOR_DEVICE_OFFLINE;
    }

    if (monitor_device->offline_flag == MONITOR_DEVICE_OFFLINE) {
        if (monitor_device->offlineCallback != NULL) {
            monitor_device->offlineCallback(monitor_device);
        }
        return MONITOR_DEVICE_OFFLINE;
    }

    monitor_device->offline_counter++;
    if (monitor_device->offline_counter >= monitor_device->offline_threshold) {
        monitor_device->offline_flag = MONITOR_DEVICE_OFFLINE;
        if (monitor_device->offlineCallback != NULL) {
            monitor_device->offlineCallback(monitor_device);
        }

        return MONITOR_DEVICE_OFFLINE;
    }

    return MONITOR_DEVICE_ONLINE;
}

void monitorCounterAll(void) {
    uint8_t i;
    for (i = 0; i < id_cnt; i++) {
        monitorCounter(monitor_devices[i]);
    }
}
