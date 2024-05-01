//=====================================================================================================
// djiMotor.h
//=====================================================================================================
//
//       IRobot  EC_lib
//
// author: @ dji
// modify: @ Specific_Cola
//
//
//
//=====================================================================================================
#ifndef DJIMOTOR_H__
#define DJIMOTOR_H__

#include "Motor/Motor_common.h"
#include "bsp_can/bsp_can.h"
#include "main.h"
#include "struct_typedef.h"

#define MAX_DJI_MOTOR_NUM 21  // 姑且算一个can7个电机
#define OFFLINE_TIME_MAX 0.1  // 单位s

typedef struct {
    uint16_t ecd;
    int16_t speed_rpm;
    int16_t given_current;
    uint8_t temperate;

} DJI_Motor_Info_t;

typedef struct {
    int16_t command;
} DJI_Command_t;

typedef struct DJI_Motor_ {
    Motor_Common_t motor_common;

    DJI_Motor_Info_t state_interfaces;
    Can_Device_t* can_info;
    DJI_Command_t command_interfaces;

    void (*motorCallback)(const struct DJI_Motor_*);
} DJI_Motor_t;

typedef struct {
    Can_Handle_t* can_handle;
    uint8_t id;

    Motor_Register_Common_t motor_register_common;
} DJI_Motor_Register_t;

DJI_Motor_t* djiMotorAdd(DJI_Motor_Register_t* reg);
void djiMotorDelete(DJI_Motor_t* motor);
void djiMotorInfoUpdate(DJI_Motor_t* motor, uint8_t* data);
Return_t djiMotorSendMessage();

#endif  // !DJIMOTOR_H__
