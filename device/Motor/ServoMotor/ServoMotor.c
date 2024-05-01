/**
 * @Author       : H0pefu12 573341043@qq.com
 * @Date         : 2024-04-17 01:28:54
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-17 03:34:24
 * @Description  : 舵机控制程序
 * @Filename     : ServoMotor.c
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */

#include "ServoMotor.h"

#include <stdlib.h>
#include <string.h>

static Servo_Motor_t* servo_motor[MAX_SERVO_MOTOR_NUM];
static uint8_t id_cnt;  // 记录大疆电机数量

/**
 * @description: 舵机注册
 * @param {Servo_Motor_Register_t*} motor_reg
 * @return {*}
 */
Servo_Motor_t* servoMotorAdd(Servo_Motor_Register_t* motor_reg) {
    Servo_Motor_t* motor = (Servo_Motor_t*)malloc(sizeof(Servo_Motor_t));
    if (motor == NULL) {
        return NULL;
    }
    memset(motor, 0, sizeof(Servo_Motor_t));

    motor->motor_type = motor_reg->motor_type;
    motor->motor_max = motor_reg->motor_max;
    motor->motor_min = motor_reg->motor_min;
    motor->motorCallback = motor_reg->motorCallback;

    PWM_Register_t pwm_reg;
    pwm_reg.htim = motor_reg->htim;
    pwm_reg.channel = motor_reg->channel;
    pwm_reg.period = 20;
    pwm_reg.dutyratio = 0;
    pwm_reg.parent = motor;
    motor->pwm_info = pwmRegister(&pwm_reg);

    motor->dutyratio_max = (20 - 2.5) / 20.0;
    motor->dutyratio_min = (20 - 0.5) / 20.0;

    // 没有反馈默认离线
    motor->statu = STATE_OFFLINE;

    servo_motor[id_cnt++] = motor;

    return motor;
}

/**
 * @description: 控制舵机
 * @param {Servo_Motor_t*} motor
 * @return {*}
 */
Return_t servoMotorSendMessage(Servo_Motor_t* motor) {
    fp32 dutyratio;
    dutyratio = (motor->command.angle - motor->motor_min) / (motor->motor_max - motor->motor_min) *
                    (motor->dutyratio_max - motor->dutyratio_min) +
                motor->dutyratio_min;

    pwmSetDuty(motor->pwm_info, 1 - dutyratio);
    return RETURN_SUCCESS;
}

/**
 * @description: 控制所有舵机
 * @param {Servo_Motor_t*} motor
 * @return {*}
 */
Return_t servoMotorSendAll() {
    for (int i = 0; i < MAX_SERVO_MOTOR_NUM; i++) {
        if (servo_motor[i] != NULL) {
            servoMotorSendMessage(servo_motor[i]);
        }
    }
    return RETURN_SUCCESS;
}

/**
 * @description: 舵机无力
 * @param {Servo_Motor_t*} motor
 * @return {*}
 */
Return_t servoMotorOff(Servo_Motor_t* motor) {
    pwmSetDuty(motor->pwm_info, 1.0);
    return RETURN_SUCCESS;
}
