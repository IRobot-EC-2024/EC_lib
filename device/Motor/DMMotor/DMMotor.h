/**
 * @Author       : H0pefu12 573341043@qq.com
 * @Date         : 2024-03-22 23:03:00
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-17 02:36:48
 * @Description  :
 * @Filename     : DMMotor.h
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#ifndef DMMOTOR_H__
#define DMMOTOR_H__

#include "Motor/Motor_common.h"
#include "bsp_can/bsp_can.h"
#include "main.h"
#include "struct_typedef.h"

#define MAX_DM_MOTOR_NUM 5
#define OFFLINE_TIME_MAX 0.1  // 单位s

typedef struct {
    uint8_t id;
    uint8_t error;
    uint16_t pos;  // 16位
    uint16_t vel;  // 12位
    uint16_t t;    // 12位
    int8_t t_mos;
    int8_t t_rotor;

    fp32 position;
    fp32 velocity;
    fp32 torque;

} DM_Motor_Info_t;

typedef struct {
    fp32 pos;
    fp32 vel;
    fp32 t;
    fp32 kd;
    fp32 kp;
} DM_MIT_Command_t;

typedef struct DM_Motor_ {
    Motor_Common_t motor_common;

    DM_Motor_Info_t state_interfaces;
    Can_Device_t* can_info;
    DM_MIT_Command_t command_interfaces;

    void (*motorCallback)(const struct DM_Motor_*);

    fp32 p_max;
    fp32 v_max;
    fp32 t_max;
    fp32 kp_max;
    fp32 kd_max;
    fp32 kp_min;
    fp32 kd_min;
} DM_Motor_t;

typedef struct {
    Motor_Register_Common_t motor_register_common;

    Can_Handle_t* can_handle;
    uint16_t rx_id;
    uint16_t tx_id;

    fp32 p_max;
    fp32 v_max;
    fp32 t_max;
    fp32 kp_max;
    fp32 kd_max;
    fp32 kp_min;
    fp32 kd_min;
} DM_Motor_Register_t;

DM_Motor_t* dmMotorAdd(DM_Motor_Register_t* reg);
void dmMotorDelete(DM_Motor_t* motor);
void dmMotorInfoUpdate(DM_Motor_t* motor, uint8_t* data);
Return_t dmMotorEnable(DM_Motor_t* motor);
void dmMotorDisable(DM_Motor_t* motor);
void dmMotorSetZero(DM_Motor_t* motor);
void dmMotorClearError(DM_Motor_t* motor);
Return_t dmMotorSendMessage(DM_Motor_t* motor);
Return_t dmMotorSendAll();

#endif
