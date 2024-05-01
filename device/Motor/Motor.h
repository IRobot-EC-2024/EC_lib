/**
 * @Author       : H0pefu12 573341043@qq.com
 * @Date         : 2024-04-01 00:59:52
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-21 02:28:40
 * @Description  :
 * @Filename     : Motor.h
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#ifndef MOTOR_H__
#define MOTOR_H__

#include "Motor/Motor_common.h"
#include "PID/controller.h"
#include "main.h"
#include "struct_typedef.h"

// 电机小类头
#include "Motor/DMMotor/DMMotor.h"
#include "Motor/RMDMotor/RMDMotor.h"
#include "Motor/ServoMotor/ServoMotor.h"
#include "Motor/djiMotor/djiMotor.h"

#define MAX_MOTOR_NUM 30      //
#define OFFLINE_TIME_MAX 0.1  // 单位s

// 电机控制方式
typedef enum {
    MOTOR_CM_COMMAND_MODE = 0,  // 不知道该选什么就选它

    MOTOR_CM_SPEED_MODE = 1,     // 速度控制
    MOTOR_CM_POSITION_MODE = 2,  // 位置控制
    MOTOR_CM_CURRENT_MODE = 3,   // 电流控制
    MOTOR_CM_TORQUE_MODE = 4,    // 转矩控制
} Motor_Control_Mode_t;

typedef enum {
    OPEN_LOOP = 0b0000,
    CURRENT_LOOP = 0b0001,
    SPEED_LOOP = 0b0010,
    ANGLE_LOOP = 0b0100,
} Closeloop_Type_t;

typedef struct {
    PIDInstance* angle_pid;
    PIDInstance* speed_pid;
    PIDInstance* current_pid;

    // 其他反馈来源的反馈数据指针
    fp32* angle_feedback;
    fp32* speed_feedback;

    fp32* fdb_src;
} Motor_Control_t;

typedef struct {
    fp32 last_angle;
    fp32 angle;
    int32_t rounds;
    fp32 series_angle;
    fp32 speed_rpm;

    fp32 current;
    fp32 torque;
    int32_t temperate;
} Motor_Info_t;

typedef struct {
    fp32 speed_rpm;
    fp32 angle;
    fp32 torque;
    fp32 current;
    fp32 voltage;
    fp32 command;

} Motor_Command_t;

typedef struct {
    Motor_Control_Mode_t control_mode;

    Motor_Info_t state_interfaces;
    Motor_Command_t command_interfaces;

    // 原始电机指针
    union {
        DJI_Motor_t* dji;
        DM_Motor_t* dm;
        RMD_Motor_t* rmd;
        Motor_Common_t* motor_common;
    };
} Motor_t;

typedef struct {
    Motor_Type_t motor_type;
    union {
        DJI_Motor_Register_t dji_motor_set;
        DM_Motor_Register_t dm_motor_set;
        RMD_Motor_Register_t rmd_motor_set;
        Motor_Register_Common_t motor_register_common;
    };
} Motor_Register_t;

typedef struct {
    PIDInstance* pid;
    float* fdb_src;

} Speed_Controller_t;
typedef struct {
    cascadePIDInstacne* cascade_pid;
    float* out_fdb_src;
    float* in_fdb_src;

} Position_Controller_t;

/***                        添加电机种类时必须修改的部分START ***/
Motor_t* motorAdd(Motor_Register_t* reg);
void motorEnable(Motor_t* motor);
void motorDisable(Motor_t* motor);

Return_t motorSendMessage(Motor_t* motor);
Return_t motorSendAll(const uint32_t mask_cmd);

// 也可以使用以下函数发送
extern Return_t djiMotorSendMessage();
extern Return_t dmMotorSendMessage(DM_Motor_t* motor);
extern Return_t dmMotorSendAll();
/***                        添加电机种类时必须修改的部分END ***/

// 电机基础控制函数
void motorSpeedControl(Motor_t* motor,
                       Speed_Controller_t* controller);  // todo    移到电机总
Speed_Controller_t* speedControllerInit(PID_Init_Config_s* config);
void motorPositionControl(Motor_t* motor, Position_Controller_t* controller);  // todo   移到电机总
Position_Controller_t* positionControllerInit(cascade_PID_Init_Config_s* config, float* out_fdb);

// 电机测试应用
bool_t motorBlockJudgment(Motor_t* motor, float speed_upper_limit);
void motor_SwitchRing(Motor_t* motor, Position_Controller_t* controller);

// todo...

// 电机闭环与发送
void motorTask(void);

#endif
