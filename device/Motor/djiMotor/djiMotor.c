//=====================================================================================================
// djiMotor.c
//=====================================================================================================
//
//       IRobot  EC_lib
//
// author: @ dji
// modify: @ Specific_Cola
//
//
//=====================================================================================================
#include "djiMotor.h"

#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "user_lib.h"

static DJI_Motor_t* dji_motor[MAX_DJI_MOTOR_NUM];
static uint8_t id_cnt;  // 记录大疆电机数量

static uint8_t MotorSendBuffer_can1[24];
static uint8_t MotorSendBuffer_can2[24];

#if defined(CAN_HANDLE3)
static uint8_t MotorSendBuffer_can3[24];
#endif

static uint32_t send_mail_box_can1;
static uint32_t send_mail_box_can2;

static void djiMotorCallback(Can_Device_t* can_device) {
    if (can_device == NULL) return;

    DJI_Motor_t* motor = can_device->parent;
    djiMotorInfoUpdate(motor, can_device->rx_buff);

    motor->motor_common.statu = STATE_ONLINE;
    if (motor->motorCallback != NULL) {
        motor->motorCallback(motor);
    }
}

DJI_Motor_t* djiMotorAdd(DJI_Motor_Register_t* reg) {
    // 使用can instance注册电机    //id就直接填写灯电调闪烁的次数
    if (id_cnt > MAX_DJI_MOTOR_NUM) {
        Error_Handler();  // 电机太多了
    }

    Can_Register_t can_reg = {};
    DJI_Motor_t* motor = (DJI_Motor_t*)malloc(sizeof(DJI_Motor_t));
    memset(motor, 0, sizeof(DJI_Motor_t));

    can_reg.can_handle = reg->can_handle;
    can_reg.tx_dlc = 8;
    can_reg.can_device_callback = djiMotorCallback;
    can_reg.can_device_offline_callback = reg->motor_register_common.motorOfflineCallback;
    can_reg.offline_threshold = 50;
    can_reg.parent = motor;

    switch (reg->motor_register_common.motor_type) {
        case DJI_MOTOR_6020:
            if (reg->id <= 4)
                can_reg.tx_id = 0x1FF;
            else if (reg->id > 4)
                can_reg.tx_id = 0x2FF;
            can_reg.rx_id = 0x204 + reg->id;
            break;
        case DJI_MOTOR_3508:
            if (reg->id <= 4)
                can_reg.tx_id = 0x200;
            else if (reg->id > 4)
                can_reg.tx_id = 0x1FF;
            can_reg.rx_id = 0x200 + reg->id;
            break;
        case DJI_MOTOR_2006:
            if (reg->id <= 4)
                can_reg.tx_id = 0x200;
            else if (reg->id > 4)
                can_reg.tx_id = 0x1FF;
            can_reg.rx_id = 0x200 + reg->id;
            break;
        default:
            Error_Handler();  // 电机类型不存在
            break;
    }

    motor->motor_common.motor_type = reg->motor_register_common.motor_type;
    motor->can_info = canDeviceRegister(&can_reg);

    dji_motor[id_cnt++] = motor;

    return motor;
}

Return_t djiMotorSendMessage() {
    int16_t can_send_num[3][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};
    Return_t ret = RETURN_SUCCESS;

    for (uint8_t i = 0; i < id_cnt; i++) {
        if (dji_motor[i]->motor_common.statu == STATE_OFFLINE) {
            dji_motor[i]->command_interfaces.command = 0;
            ret = RETURN_ERROR;
            continue;
        }

        if (dji_motor[i]->can_info->can_handle == &CAN_HANDLE1) {
            MotorSendBuffer_can1[(dji_motor[i]->can_info->rx_id - 0x201) * 2] =
                dji_motor[i]->command_interfaces.command >> 8;
            MotorSendBuffer_can1[(dji_motor[i]->can_info->rx_id - 0x201) * 2 + 1] =
                dji_motor[i]->command_interfaces.command;

            switch (dji_motor[i]->can_info->tx_id) {
                case 0x200:
                    can_send_num[0][0] = i;
                    break;
                case 0x1FF:
                    can_send_num[0][1] = i;
                    break;
                case 0x2FF:
                    can_send_num[0][2] = i;
                    break;
            }
        } else if (dji_motor[i]->can_info->can_handle == &CAN_HANDLE2) {
            MotorSendBuffer_can2[(dji_motor[i]->can_info->rx_id - 0x201) * 2] =
                dji_motor[i]->command_interfaces.command >> 8;
            MotorSendBuffer_can2[(dji_motor[i]->can_info->rx_id - 0x201) * 2 + 1] =
                dji_motor[i]->command_interfaces.command;

            switch (dji_motor[i]->can_info->tx_id) {
                case 0x200:
                    can_send_num[1][0] = i;
                    break;
                case 0x1FF:
                    can_send_num[1][1] = i;
                    break;
                case 0x2FF:
                    can_send_num[1][2] = i;
                    break;
            }
        }
#ifdef CAN_HANDLE3
        else if (dji_motor[i]->can_info->can_handle == &CAN_HANDLE3) {
            MotorSendBuffer_can3[(dji_motor[i]->can_info->rx_id - 0x201) * 2] =
                dji_motor[i]->command_interfaces.command >> 8;
            MotorSendBuffer_can3[(dji_motor[i]->can_info->rx_id - 0x201) * 2 + 1] =
                dji_motor[i]->command_interfaces.command;

            switch (dji_motor[i]->can_info->tx_id) {
                case 0x200:
                    can_send_num[2][0] = i;
                    break;
                case 0x1FF:
                    can_send_num[2][1] = i;
                    break;
                case 0x2FF:
                    can_send_num[2][2] = i;
                    break;
            }
        }
#endif
    }

    if (can_send_num[0][0] >= 0) {
        canSendMessage(dji_motor[can_send_num[0][0]]->can_info, MotorSendBuffer_can1);
    }
    if (can_send_num[0][1] >= 0) {
        canSendMessage(dji_motor[can_send_num[0][1]]->can_info, MotorSendBuffer_can1 + 8);
    }
    if (can_send_num[0][2] >= 0) {
        canSendMessage(dji_motor[can_send_num[0][2]]->can_info, MotorSendBuffer_can1 + 16);
    }

    if (can_send_num[1][0] >= 0) {
        canSendMessage(dji_motor[can_send_num[1][0]]->can_info, MotorSendBuffer_can2);
    }
    if (can_send_num[1][1] >= 0) {
        canSendMessage(dji_motor[can_send_num[1][1]]->can_info, MotorSendBuffer_can2 + 8);
    }
    if (can_send_num[1][2] >= 0) {
        canSendMessage(dji_motor[can_send_num[1][2]]->can_info, MotorSendBuffer_can2 + 16);
    }

    return ret;
}

void djiMotorInfoUpdate(DJI_Motor_t* motor, uint8_t* data) {
    motor->state_interfaces.ecd = (uint16_t)((data)[0] << 8 | (data)[1]);
    motor->state_interfaces.speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]);
    motor->state_interfaces.given_current = (uint16_t)((data)[4] << 8 | (data)[5]);
    motor->state_interfaces.temperate = (data)[6];
}
