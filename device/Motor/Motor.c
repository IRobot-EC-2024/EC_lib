/**
 * @Author       : H0pefu12 573341043@qq.com
 * @Date         : 2024-04-01 00:59:52
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-19 20:04:06
 * @Description  : 电机总类，目标是将电机种类和控制方式解耦，实现电机种类和控制方式的可插拔
 * @Filename     : Motor.c
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#include "Motor.h"

#include <stdlib.h>
#include <string.h>

#include "arm_math.h"
#include "main.h"
#include "user_lib.h"

static Motor_t* motor_instance[MAX_MOTOR_NUM];
static uint8_t id_cnt = 0;  // 记录电机数量

#define get_motor_mask(indicator) ((indicator)->motor_common->motor_type & 0xFFF0)

/***                        添加电机种类时必须修改的部分START ***/
static void djiMotorInfo(const DJI_Motor_t* motor);
static void dmMotorInfo(const DM_Motor_t* motor);
static void rmdMotorInfo(const RMD_Motor_t* motor);
static void motorOfflineCallback(Can_Device_t* can_device);

Motor_t* motorAdd(Motor_Register_t* reg) {
    uint16_t motor_mask = (reg->motor_type & 0xFFF0);

    Motor_t* motor = (Motor_t*)malloc(sizeof(Motor_t));
    if (motor == NULL) return NULL;
    memset(motor, 0, sizeof(Motor_t));

    switch (motor_mask) {
        case DJI_MOTOR_MASK: {
            reg->dji_motor_set.motor_register_common.motor_type = reg->motor_type;
            reg->dji_motor_set.motor_register_common.motorOfflineCallback = motorOfflineCallback;
            motor->dji = djiMotorAdd(&reg->dji_motor_set);
            motor->dji->motorCallback = djiMotorInfo;
        } break;

        case DM_MOTOR_MASK: {
            motor->dm = dmMotorAdd(&reg->dm_motor_set);
            motor->dm->motorCallback = dmMotorInfo;
        } break;

        case RMD_MOTOR_MASK: {
            motor->rmd = rmdMotorAdd(&reg->rmd_motor_set);
            motor->rmd->motorCallback = rmdMotorInfo;
        } break;
        default: {
        } break;
    }

    motor->motor_common->common = motor;
    motor_instance[id_cnt] = motor;
    id_cnt++;

    return motor;
}

void motorEnable(Motor_t* motor) {
    uint16_t motor_mask;
    motor_mask = get_motor_mask(motor);
    switch (motor_mask) {
        case DJI_MOTOR_MASK: {
        } break;

        case DM_MOTOR_MASK: {
            dmMotorEnable(motor->dm);
        } break;
    }
}
void motorDisable(Motor_t* motor) {
    uint16_t motor_mask;
    motor_mask = get_motor_mask(motor);
    switch (motor_mask) {
        case DJI_MOTOR_MASK: {
        } break;

        case DM_MOTOR_MASK: {
            dmMotorDisable(motor->dm);
        } break;

        case RMD_MOTOR_MASK: {
        } break;
    }
}

Return_t motorSetMessage(Motor_t* motor) {
    Return_t ret = RETURN_SUCCESS;
    uint16_t motor_mask;
    motor_mask = get_motor_mask(motor);
    switch (motor_mask) {
        case DJI_MOTOR_MASK: {
            if (motor->control_mode == MOTOR_CM_COMMAND_MODE) {
                motor->dji->command_interfaces.command = motor->command_interfaces.command;
            } else {
                // todo：dji电机其他控制模式
                ret = RETURN_ERROR;
            }
        } break;

        case DM_MOTOR_MASK: {
            if (motor->control_mode == MOTOR_CM_COMMAND_MODE) {
                motor->dm->command_interfaces.t = motor->command_interfaces.command;
            } else {
                // todo: dm电机其他控制模式
                ret = RETURN_ERROR;
            }
        } break;

        case RMD_MOTOR_MASK: {
            if (motor->control_mode == MOTOR_CM_COMMAND_MODE) {
                motor->rmd->command_interfaces.iqControl = motor->command_interfaces.command;
            } else {
                // todo: rmd电机其他控制模式
                ret = RETURN_ERROR;
            }
        } break;
    }
    return ret;
}

Return_t motorSendMessage(Motor_t* motor) {
    if (motor == NULL) return RETURN_ERROR;
    Return_t ret = RETURN_SUCCESS;

    ret = motorSetMessage(motor);

    uint16_t motor_mask;
    motor_mask = get_motor_mask(motor);
    switch (motor_mask) {
        case DJI_MOTOR_MASK: {
            ret = RETURN_ERROR;
            // 大疆电机无法单独发送
        } break;

        case DM_MOTOR_MASK: {
            dmMotorSendMessage(motor->dm);
        } break;

        case RMD_MOTOR_MASK: {
            rmdMotorSendMessage(motor->rmd);
        } break;
    }

    return ret;
}

Return_t motorSendAll(const uint32_t mask_cmd) {
    Return_t ret = RETURN_SUCCESS;

    uint8_t i = 0;

    uint16_t motor_mask;
    motor_mask = mask_cmd & 0xFFF0;

    for (i = 0; i < id_cnt; i++) {
        if (get_motor_mask(motor_instance[i]) == motor_mask) {
            ret |= motorSendMessage(motor_instance[i]);
        }
    }

    if (motor_mask == DJI_MOTOR_MASK) ret |= djiMotorSendMessage();

    return ret;
}

/***                        添加电机种类时必须修改的部分END ***/

void motorSpeedControl(Motor_t* motor, Speed_Controller_t* controller) {
    motor->command_interfaces.command =
        (int16_t)PIDCalculate(controller->pid, motor->state_interfaces.speed_rpm, motor->command_interfaces.speed_rpm);
}

Speed_Controller_t* speedControllerInit(PID_Init_Config_s* config) {
    Speed_Controller_t* controller = (Speed_Controller_t*)malloc(sizeof(Speed_Controller_t));
    memset(controller, 0, sizeof(Speed_Controller_t));
    PIDInstance* instance = (PIDInstance*)malloc(sizeof(PIDInstance));
    PIDInit(instance, config);
    controller->pid = instance;

    return controller;
}
Position_Controller_t* positionControllerInit(cascade_PID_Init_Config_s* config, float* out_fdb) {
    Position_Controller_t* controller = (Position_Controller_t*)malloc(sizeof(Position_Controller_t));
    memset(controller, 0, sizeof(Position_Controller_t));
    cascadePIDInstacne* instance = (cascadePIDInstacne*)malloc(sizeof(cascadePIDInstacne));
    cascadePIDInit(instance, config);
    controller->out_fdb_src = out_fdb;
    controller->cascade_pid = instance;
    return controller;
}

void motorPositionControl(Motor_t* motor, Position_Controller_t* controller) {
    motor->command_interfaces.angle = loop_float_constrain(
        motor->command_interfaces.angle, *controller->out_fdb_src - 180.f, *controller->out_fdb_src + 180.f);
    motor->command_interfaces.command =
        cascadePIDCalculate(controller->cascade_pid, *controller->out_fdb_src, motor->state_interfaces.speed_rpm,
                            motor->command_interfaces.angle);
}
void motor_SwitchRing(Motor_t* motor, Position_Controller_t* controller) {
    if (motor->state_interfaces.angle - motor->command_interfaces.angle > 5.0f)
        motor->command_interfaces.angle += 10.0f;
    else if (motor->state_interfaces.angle - motor->command_interfaces.angle < -5.0f)
        motor->command_interfaces.angle -= 10.0f;

    motorPositionControl(motor, controller);
}

/**
 * @description: dji电机信息标准化
 * @param {DJI_Motor_t*} motor
 * @return {*}
 */
static void djiMotorInfo(const DJI_Motor_t* motor) {
    if (motor == NULL || motor->motor_common.common == NULL) return;

    Motor_t* instance = motor->motor_common.common;

    instance->state_interfaces.last_angle = instance->state_interfaces.angle;
    instance->state_interfaces.angle = motor->state_interfaces.ecd / 8191.0 * 360;
    instance->state_interfaces.current = motor->state_interfaces.given_current;
    instance->state_interfaces.speed_rpm = motor->state_interfaces.speed_rpm;
    instance->state_interfaces.temperate = motor->state_interfaces.temperate;
    instance->state_interfaces.torque = 0;

    // 转速不可高于45000rpm
    if ((instance->state_interfaces.angle - instance->state_interfaces.last_angle) > 180) {
        instance->state_interfaces.rounds--;
    } else if ((instance->state_interfaces.angle - instance->state_interfaces.last_angle) < -180) {
        instance->state_interfaces.rounds++;
    }

    instance->state_interfaces.series_angle =
        instance->state_interfaces.angle + 360 * instance->state_interfaces.rounds;
}

/**
 * @description: dm电机信息标准化
 * @param {DM_Motor_t*} motor
 * @return {*}
 */
static void dmMotorInfo(const DM_Motor_t* motor) {
    if (motor == NULL || motor->motor_common.common == NULL) return;

    Motor_t* instance = motor->motor_common.common;
    instance->state_interfaces.last_angle = instance->state_interfaces.angle;
    instance->state_interfaces.angle = loop_float_constrain(motor->state_interfaces.position / PI * 180, 0, 360);

    instance->state_interfaces.current = 0;
    instance->state_interfaces.speed_rpm = motor->state_interfaces.velocity / PI * 60;
    instance->state_interfaces.temperate = motor->state_interfaces.t_mos;
    instance->state_interfaces.torque = motor->state_interfaces.torque;

    if ((instance->state_interfaces.angle - instance->state_interfaces.last_angle) > 180) {
        instance->state_interfaces.rounds--;
    } else if ((instance->state_interfaces.angle - instance->state_interfaces.last_angle) < -180) {
        instance->state_interfaces.rounds++;
    }

    instance->state_interfaces.series_angle =
        instance->state_interfaces.angle + 360 * instance->state_interfaces.rounds;
}

/**
 * @description: rmd电机信息标准化
 * @param {RMD_Motor_t*} motor
 * @return {*}
 */
static void rmdMotorInfo(const RMD_Motor_t* motor) {
    if (motor == NULL || motor->motor_common.common == NULL) return;

    Motor_t* instance = motor->motor_common.common;
    instance->state_interfaces.last_angle = instance->state_interfaces.angle;
    instance->state_interfaces.angle = loop_float_constrain(motor->state_interfaces.encoder / 16383.0 * 360, 0, 360);

    instance->state_interfaces.current = motor->state_interfaces.iq / 2000.0 * 32;
    instance->state_interfaces.speed_rpm = motor->state_interfaces.speed / PI * 60;
    instance->state_interfaces.temperate = motor->state_interfaces.temperature;

    if ((instance->state_interfaces.angle - instance->state_interfaces.last_angle) > 180) {
        instance->state_interfaces.rounds--;
    } else if ((instance->state_interfaces.angle - instance->state_interfaces.last_angle) < -180) {
        instance->state_interfaces.rounds++;
    }

    instance->state_interfaces.series_angle =
        instance->state_interfaces.angle + 360 * instance->state_interfaces.rounds;
}

static void motorOfflineCallback(Can_Device_t* can_device) {
    if (can_device == NULL || can_device->parent == NULL) return;
    Motor_t* motor = ((Motor_Common_t*)can_device->parent)->common;
    if (motor == NULL) return;
    motor->motor_common->statu = STATE_OFFLINE;
    memset(&motor->state_interfaces, 0, sizeof(Motor_Info_t));
    memset(&motor->command_interfaces, 0, sizeof(Motor_Common_t));
}

bool_t motorBlockJudgment(Motor_t* motor, float speed_upper_limit) {
    bool_t flag = FALSE;
    if (fabs(motor->state_interfaces.speed_rpm) < speed_upper_limit) {
        flag = TRUE;
    }
    return flag;
}

void motorTask(void) {
   for (int i = 0; i < id_cnt; i++) {
   }
}
