//=====================================================================================================
// RMDMotor.c
//=====================================================================================================
//
//       IRobot  EC_lib
//
// author: @ dji
// modify: @ Specific_Cola
// 
//
//=====================================================================================================
#include "RMDMotor.h"
#include "main.h"
#include <stdlib.h>
#include <string.h>
#include "user_lib.h"

static RMD_Motor_t *rmd_motor[MAX_RMD_MOTOR_NUM];
static uint8_t id_cnt; //记录大疆电机数量

static uint8_t motor_send_buffer[8];

static void rmdMotorCallback(Can_Device_t *instance)
{
    for(uint8_t i = 0; i < id_cnt;i++)
    {
        if(instance == rmd_motor[i]->can_info)
        {
            rmdMotorInfoUpdate(rmd_motor[i],instance->rx_buff);
			
			if(rmd_motor[i]->motorCallback!=NULL){
				rmd_motor[i]->motorCallback(rmd_motor[i]);
			}
			
            break;
        }
    }     
}

RMD_Motor_t *rmdMotorAdd(RMD_Motor_Register_t *reg)
{
    if (id_cnt > MAX_RMD_MOTOR_NUM) 
    {
        Error_Handler();//电机太多了
    }
    
    Can_Register_t can_reg;
    RMD_Motor_t *motor = (RMD_Motor_t *)malloc(sizeof(RMD_Motor_t));
    memset(&can_reg, 0, sizeof(Can_Register_t));
    memset(motor, 0, sizeof(RMD_Motor_t));
	
    can_reg.can_handle = reg->hcan;
    can_reg.tx_dlc = 8; 
    can_reg.can_device_callback = rmdMotorCallback;
	
    switch (reg->motor_type)
    {
    case RMD_MOTOR_4015:
        can_reg.rx_id = 0x140 + reg->id;
        can_reg.tx_id = 0x140 + reg->id;
        break;
    default:
        Error_Handler();//电机类型不存在
        break;
    }
    
    motor->motor_type = reg->motor_type;
    motor->can_info = canDeviceRegister(&can_reg);
    
    rmd_motor[id_cnt++] = motor;

    return motor;   
}

Return_t rmdMotorSendMessage(RMD_Motor_t *motor){
	

	if(motor->statu == OFFLINE){
		memset(&motor->command_interfaces,0,sizeof(motor->command_interfaces));
		return RETURN_ERROR;
	}
	
	
	
	motor_send_buffer[0]= 0xA1;
	motor_send_buffer[1]= 0;
	motor_send_buffer[2]= 0;
	motor_send_buffer[3]= 0;
	motor_send_buffer[4]= *(uint8_t *)(&motor->command_interfaces.iqControl);
	motor_send_buffer[5]= *((uint8_t *)(&motor->command_interfaces.iqControl)+1);
	motor_send_buffer[6]= 0;
	motor_send_buffer[7]= 0;

	
	return canSendMessage(motor->can_info,motor_send_buffer);
}

void rmdMotorInfoUpdate(RMD_Motor_t *motor,uint8_t *data)
{
    motor->state_interfaces.cmd_id = (data)[0];
	
	switch(motor->state_interfaces.cmd_id){
		case 0xA1:
		case 0xA2:
		case 0xA3:
		case 0xA4:
		case 0xA5:
		case 0xA6:
		case 0xA7:
		case 0xA8:
		{
			motor->state_interfaces.temperature = (data)[1];
			motor->state_interfaces.iq = (uint16_t)((data)[3] << 8 | (data)[2]);
			motor->state_interfaces.speed = (uint16_t)((data)[5] << 8 | (data)[4]);
			motor->state_interfaces.encoder = (uint16_t)((data)[7] << 8 | (data)[6]);
		}
		break;
	}
}


