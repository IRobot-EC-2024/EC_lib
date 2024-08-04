/**
 * @Author       : H0pefu12 573341043@qq.com
 * @Date         : 2024-04-17 01:29:11
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-17 03:10:14
 * @Description  :
 * @Filename     : ServoMotor.h
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#ifndef SERVOMOTOR_H__
#define SERVOMOTOR_H__

#include "Motor/Motor_common.h"
#include "bsp_pwm/bsp_pwm.h"
#include "main.h"
#include "struct_typedef.h"

#define MAX_SERVO_MOTOR_NUM 4

typedef struct {
    fp32 angle;
} Servo_Command_t;

typedef struct Servo_Motor_ {
    uint8_t statu;  // online 0  / offline 1
    Motor_Type_t motor_type;
    PWM_Device_t* pwm_info;

    Servo_Command_t command;

    void (*motorCallback)(struct Servo_Motor_*);

    fp32 motor_max;
    fp32 motor_min;
    fp32 dutyratio_max;
    fp32 dutyratio_min;
} Servo_Motor_t;

typedef struct {
    Motor_Type_t motor_type;
    TIM_HandleTypeDef* htim;  // TIM句柄
    uint32_t channel;         // 通道

    void (*motorCallback)(Servo_Motor_t*);

    fp32 motor_max;
    fp32 motor_min;
} Servo_Motor_Register_t;

Servo_Motor_t* servoMotorAdd(Servo_Motor_Register_t* reg);
Return_t servoMotorSendMessage(Servo_Motor_t* motor);
Return_t servoMotorSendAll(void);
Return_t servoMotorOff(Servo_Motor_t* motor);
Return_t servoMotorOn(Servo_Motor_t* motor);

#endif
