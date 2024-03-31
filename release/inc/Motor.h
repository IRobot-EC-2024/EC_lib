//=====================================================================================================
// Motor.h
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
#ifndef MOTOR_H__
#define MOTOR_H__

#include "main.h"
#include "struct_typedef.h"
#include "controller.h"

#include "djiMotor.h"
#include "DMMotor.h"
#include "RMDMotor.h"


#define MAX_MOTOR_NUM      30 //
#define OFFLINE_TIME_MAX       0.1//单位s

typedef struct{
    fp32 last_angle;
    fp32 angle;
    int32_t rounds;
    fp32 series_angle;
    fp32 speed_rpm;
	
    fp32 current;
    fp32 torque;
    int32_t temperate;
}Motor_Info_t;

typedef struct{
    fp32 speed_rpm;
    fp32 angle;
	fp32 torque;
	fp32 current;
    fp32 voltage;
    fp32 command;
	
}Motor_Command_t;

typedef struct{
	uint8_t statu;  //online 0  / offline 1 
	uint32_t motor_type;
    Motor_Info_t state_interfaces;
    Motor_Command_t command_interfaces;
	
	union{
		DJI_Motor_t *dji;
		DM_Motor_t 	*dm;
		RMD_Motor_t	*rmd;
	};
	
}Motor_t;

typedef union{
	DJI_Motor_Register_t dji_motor_set;
	DM_Motor_Register_t dm_motor_set;
	RMD_Motor_Register_t rmd_motor_set;
	struct{
		uint32_t motor_type;
	};
}Motor_Register_t;

typedef struct{
    
    PIDInstance *pid;
    float *fdb_src;

}Speed_Controller_t;
typedef struct{

    cascadePIDInstacne *cascade_pid;
    float *out_fdb_src;
    float *in_fdb_src;

}Position_Controller_t;

/***                        添加电机种类时必须修改的部分START                                         ***/
Motor_t *motorAdd(Motor_Register_t *reg);
void motorEnable(Motor_t *motor);
void motorDisable(Motor_t *motor);

Return_t motorSendMessage(Motor_t *motor);
Return_t motorSendAll();

//也可以使用以下函数发送
extern Return_t djiMotorSendMessage();
extern Return_t dmMotorSendMessage(DM_Motor_t *motor);
extern Return_t dmMotorSendAll();
/***                        添加电机种类时必须修改的部分END                                         ***/



//电机基础控制函数
void motorSpeedControl(Motor_t *motor,Speed_Controller_t *controller);//todo    移到电机总
Speed_Controller_t *speedControllerInit(PID_Init_Config_s *config);
void motorPositionControl(Motor_t *motor,Position_Controller_t *controller);//todo   移到电机总
Position_Controller_t *positionControllerInit(cascade_PID_Init_Config_s *config,float *out_fdb);

//电机测试应用
bool_t motorBlockJudgment(Motor_t *motor,float speed_upper_limit);
void motor_SwitchRing(Motor_t *motor,Position_Controller_t *controller);



#endif