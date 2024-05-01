/**
 * @Author       : H0pefu12 573341043@qq.com
 * @Date         : 2024-04-01 00:59:52
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-21 02:28:40
 * @Description  : 电机通用定义
 * @Filename     : Motor_common.h
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#ifndef MOTOR_COMMON_H__
#define MOTOR_COMMON_H__

#include "bsp_can/bsp_can.h"
#include "struct_typedef.h"

#define MOTOR_OFFLINE_THRESHOLD 50  // ms

typedef enum {
    DJI_MOTOR_MASK = 0x10,
    DJI_MOTOR_6020 = 0x11,
    DJI_MOTOR_3508 = 0x12,
    DJI_MOTOR_2006 = 0x13,

    DM_MOTOR_MASK = 0x20,
    DM_MOTOR_4310 = 0x21,

    RMD_MOTOR_MASK = 0x30,
    RMD_MOTOR_4015 = 0x31,

    SERVO_MOTOR_ANGLE = 0xF1,
    SERVO_MOTOR_SPEED = 0xF2,

} Motor_Type_t;

typedef struct {
    uint8_t statu;
    Motor_Type_t motor_type;
    void* common;
} Motor_Common_t;

typedef struct {
    Motor_Type_t motor_type;
    void (*motorOfflineCallback)(Can_Device_t* can_device);
} Motor_Register_Common_t;

#endif
