/**
 * @Author       : H0pefu12 573341043@qq.com
 * @Date         : 2024-04-15 09:51:44
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-17 02:36:17
 * @Description  :
 * @Filename     : RMDMotor.h
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#ifndef RMDMOTOR_H__
#define RMDMOTOR_H__

#include "Motor/Motor_common.h"
#include "bsp_can/bsp_can.h"
#include "main.h"
#include "struct_typedef.h"

#define MAX_RMD_MOTOR_NUM 3   // 姑且算一个can7个电机
#define OFFLINE_TIME_MAX 0.1  // 单位s

typedef struct {
    uint8_t cmd_id;
    int8_t temperature;
    int16_t iq;
    int16_t speed;
    uint16_t encoder;
} RMD_Motor_Info_t;

typedef struct {
    int16_t iqControl;
} RMD_Command_t;

typedef struct RMD_Motor_ {
    Motor_Common_t motor_common;

    RMD_Motor_Info_t state_interfaces;
    Can_Device_t* can_info;
    RMD_Command_t command_interfaces;

    void (*motorCallback)(const struct RMD_Motor_*);
} RMD_Motor_t;

typedef struct {
    Motor_Register_Common_t motor_register_common;

    Can_Handle_t* can_handle;
    uint8_t id;
} RMD_Motor_Register_t;

RMD_Motor_t* rmdMotorAdd(RMD_Motor_Register_t* reg);
void rmdMotorDelete(RMD_Motor_t* motor);
Return_t rmdMotorEnable(RMD_Motor_t* motor);
void rmdMotorInfoUpdate(RMD_Motor_t* motor, uint8_t* data);
Return_t rmdMotorSendMessage(RMD_Motor_t* motor);

#endif  // !RMDMOTOR_H__
