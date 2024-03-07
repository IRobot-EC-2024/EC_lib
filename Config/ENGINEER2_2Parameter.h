
#ifndef __ENGINEER2_2_Parameter
#define __ENGINEER2_2_Parameter

#define HIGH_CAR_SPEED 600//1300
#define MEDIUM_CAR_SPEED 350//280
#define SLOW_CAR_SPEED 100

//定义长按时间
#define LONG_PRESSED_TIME 1000

#define MEDUIM_ECD 194.0
#define AHEAD_ECD  283.0
#define BACK_ECD   105.00

//小资源岛升降高度
#define LITTLE_ISLAND_OF_RESOURCES_0   Lift_motor_start_angle[0]+230
#define LITTLE_ISLAND_OF_RESOURCES_1   Lift_motor_start_angle[1]-230
//大资源岛升降高度
#define BIG_ISLAND_OF_RESOURCES_0 	   Lift_motor_start_angle[0]+230	
#define BIG_ISLAND_OF_RESOURCES_1      Lift_motor_start_angle[1]-230
//存矿高度
#define SAVE_MINE_HEIGHT_0             Lift_motor_start_angle[0]+260
#define SAVE_MINE_HEIGHT_1				     Lift_motor_start_angle[1]-260
//抬矿
#define LIFT_MINE_HEIGHT_0             Lift_motor_start_angle[0]+340
#define LIFT_MINE_HEIGHT_1				     Lift_motor_start_angle[1]-340

//兑换站大致高度
#define EXCHANGE_STATION_HEIGHT_0		 Lift_motor_start_angle[0]+280
#define EXCHANGE_STATION_HEIGHT_1		 Lift_motor_start_angle[0]-280

//保持时的目标速度
#define LEFT_MAINTAIN_SPEED  -5
#define RIGHT_MAINTAIN_SPEED  5
//空接pid目标速度
#define LIFT_SPEED 5400
//下降pid目标速度
#define DOWN_SPEED 3000
//兑换模式自动抬升
#define EXCHANGE_UPWARD_SPEED_AUTO 5000
//兑换模式手动向上抬升目标速度
#define EXCHANGE_UPWARD_SPEED 2800
#define EXCHANGE_UPWARD_SPEED_SLOWLY 800
//兑换模式手动向下下降目标速度
#define EXCHANGE_DOWNWARD_SPEED -2800
#define EXCHANGE_DOWNWARD_SPEED_SLOWLY -800

//资源岛模式向下抓矿下降目标速度
#define ISLAND_DOWNWARD_SPEED -600

//双环位置反馈死区
#define REACH_BAND  10

//底盘速度环参数
#define CHASSIS_SPEED_PID_KP 20
#define CHASSIS_SPEED_PID_KI 0
#define CHASSIS_SPEED_PID_KD 0

#define CHASSIS_SPEED_PID_MAX M3508_MAX_OUTPUT

//#define CHASSIS_SPEED_FAST_PID_KP 25
//#define CHASSIS_SPEED_FAST_PID_KI 0
//#define CHASSIS_SPEED_FAST_PID_KD 0

//#define CHASSIS_SPEED_SLOW_PID_KP 15
//#define CHASSIS_SPEED_SLOW_PID_KI 0
//#define CHASSIS_SPEED_SLOW_PID_KD 0


////保持抬升左速度环参数
//#define LIFT_MOTOR_LEFT_CONUTINE_SPEED_PID_KP 25
//#define LIFT_MOTOR_LEFT_CONUTINE_SPEED_PID_KI 0.01	
//#define LIFT_MOTOR_LEFT_CONUTINE_SPEED_PID_KD 0

////保持抬升右速度环参
//#define LIFT_MOTOR_RIGHT_CONUTINE_SPEED_PID_KP 25		
//#define LIFT_MOTOR_RIGHT_CONUTINE_SPEED_PID_KI 0.01		
//#define LIFT_MOTOR_RIGHT_CONUTINE_SPEED_PID_KD 0

////空接抬升左速度环参数
//#define LIFT_MOTOR_LEFT_SPEED_PID_KP 5.35	
//#define LIFT_MOTOR_LEFT_SPEED_PID_KI 0.01	
//#define LIFT_MOTOR_LEFT_SPEED_PID_KD 0

//视觉抬升速度环参数
#define VIEW_LIFT_MOTOR_SPEED_PID_KP 4		
#define VIEW_LIFT_MOTOR_SPEED_PID_KI 0		
#define VIEW_LIFT_MOTOR_SPEED_PID_KD 0

//视觉抬升角度环参数
#define VIEW_LIFT_MOTOR_ANGLE_PID_KP 60	
#define VIEW_LIFT_MOTOR_ANGLE_PID_KI 0.01		
#define VIEW_LIFT_MOTOR_ANGLE_PID_KD 0

#define VIEW_LIFT_MOTOR_SPEED_MAX 		M2006_MAX_OUTPUT
#define VIEW_LIFT_MOTOR_SPEED_IMAX 		M2006_MAX_IOUTPUT
#define VIEW_LIFT_MOTOR_ANGLE_MAX 		4000
#define VIEW_LIFT_MOTOR_ANGLE_IMAX 		1000

//抬升左速度环参数
#define LIFT_MOTOR_LEFT_SPEED_KP 4
#define LIFT_MOTOR_LEFT_SPEED_KI 0
#define LIFT_MOTOR_LEFT_SPEED_KD 0

//抬升右速度环参数
#define LIFT_MOTOR_RIGHT_SPEED_KP 4
#define LIFT_MOTOR_RIGHT_SPEED_KI 0		
#define LIFT_MOTOR_RIGHT_SPEED_KD 0

//抬升左角度环参数
#define LIFT_MOTOR_LEFT_ANGLE_KP 70		
#define LIFT_MOTOR_LEFT_ANGLE_KI 0.02
#define LIFT_MOTOR_LEFT_ANGLE_KD 0

//抬升右角度环参数
#define LIFT_MOTOR_RIGHT_ANGLE_KP 70
#define LIFT_MOTOR_RIGHT_ANGLE_KI 0.02//0.2
#define LIFT_MOTOR_RIGHT_ANGLE_KD 0

#define LIFT_MOTOR_LEFT_SPEED_MAX 		M3508_MAX_OUTPUT
#define LIFT_MOTOR_LEFT_SPEED_IMAX 		M3508_MAX_IOUTPUT
#define LIFT_MOTOR_LEFT_ANGLE_MAX 		4000
#define LIFT_MOTOR_LEFT_ANGLE_IMAX 		1000

#define LIFT_MOTOR_RIGHT_SPEED_MAX 		M3508_MAX_OUTPUT
#define LIFT_MOTOR_RIGHT_SPEED_IMAX 		M3508_MAX_IOUTPUT
#define LIFT_MOTOR_RIGHT_ANGLE_MAX 		4000
#define LIFT_MOTOR_RIGHT_ANGLE_IMAX 		1000
////存矿抬升左速度环参数
//#define SAVE_CASCADE_LIFT_MOTOR_LEFT_SPEED_KP 5
//#define SAVE_CASCADE_LIFT_MOTOR_LEFT_SPEED_KI 0		
//#define SAVE_CASCADE_LIFT_MOTOR_LEFT_SPEED_KD 0

////存矿抬升右速度环参数
//#define SAVE_CASCADE_RIGHT_MOTOR_LEFT_SPEED_KP 5
//#define SAVE_CASCADE_RIGHT_MOTOR_LEFT_SPEED_KI 0		
//#define SAVE_CASCADE_RIGHT_MOTOR_LEFT_SPEED_KD 0

////存矿抬升左角度环参数
//#define SAVE_LIFT_MOTOR_LEFT_ANGLE_PID_KP 50		
//#define SAVE_LIFT_MOTOR_LEFT_ANGLE_PID_KI 0.05
//#define  SAVE_LIFT_MOTOR_LEFT_ANGLE_PID_KD 0

////存矿抬升右角度环参数
//#define  SAVE_LIFT_MOTOR_RIGHT_ANGLE_PID_KP 50
//#define  SAVE_LIFT_MOTOR_RIGHT_ANGLE_PID_KI 0.05//0.2
//#define  SAVE_LIFT_MOTOR_RIGHT_ANGLE_PID_KD 0

//救援卡速度环参数
#define HELP_CARD_SPEED_PID_KP 50
#define HELP_CARD_SPEED_PID_KI 0
#define HELP_CARD_SPEED_PID_KD 0

//救援卡位置环参数
#define HELP_CARD_ANGLE_PID_KP 60
#define HELP_CARD_ANGLE_PID_KI 0.3
#define HELP_CARD_ANGLE_PID_KD 0

//钩爪救援速度环参数
#define HELP_MOTO_SPEED_PID_KP 1.2
#define HELP_MOTO_SPEED_PID_KI 0.3
#define HELP_MOTO_SPEED_PID_KD 0

//障碍块速度环参数
#define BLOCK_MOTO_SPEED_PID_KP 2
#define BLOCK_MOTO_SPEED_PID_KI 0.2
#define BLOCK_MOTO_SPEED_PID_KD 0


//云台YAW速度环参数
#define VIEW_MOTO_YAW_SPEED_KP 1
#define VIEW_MOTO_YAW_SPEED_KI 0
#define VIEW_MOTO_YAW_SPEED_KD 0

//云台YAW角度环参数
#define VIEW_MOTO_YAW_ANGLE_KP 6    //9
#define VIEW_MOTO_YAW_ANGLE_KI 0.25  //0.03
#define VIEW_MOTO_YAW_ANGLE_KD 0.8   //100

//云台抬升参数
#define VIEW_LIFT_SPEED 4000


//云台抬升速度环参数
#define VIEW_LIFT_SPEED_KP 10
#define VIEW_LIFT_SPEED_KI 0.01
#define VIEW_LIFT_SPEED_KD 0


//云台抬升速度环参数
#define VIEW_LIFT_CONTIUNE_SPEED_KP 5
#define VIEW_LIFT_CONTIUNE_SPEED_KI 0
#define VIEW_LIFT_CONTIUNE_SPEED_KD 0

//云台抬升最大输出
#define VIEW_LIFT_MOTOR_MAX_OUT  8000
#define VIEW_LIFT_MOTOR_MAX_IOUT  2000

//救援卡最大输出
#define HELP_CARD_MOTO_SPEED_MAX_OUT 6500
#define HELP_CARD_MOTO_SPEED_MAX_IOUT 3000
#define HELP_CARD_MOTO_ANGLE_MAX_OUT 270
#define HELP_CARD_MOTO_ANGLE_MAX_IOUT 3

//钩爪救援最大输出
#define HELP_MOTO_SPEED_MAX_OUT 1800
#define HELP_MOTO_SPEED_MAX_IOUT 100

//障碍块最大输出
#define BLOCK_MOTO_SPEED_MAX_OUT 4000
#define BLOCK_MOTO_SPEED_MAX_IOUT 2000

//最大YAW速度输出
#define MAX_YAW_SPEED_OUT 	400.0f				//3800.0f
#define MAX_YAW_SPEED_IOUT  50.0f

//最大YAW角度输出
#define MAX_YAW_ANGLE_OUT 1000.0f
#define MAX_YAW_ANGLE_IOUT 50.0f		//150.0f

//保持抬升最大输出
#define LIFT_MOTOR_CONUTINE_SPEED_MAX_OUT  8000
#define LIFT_MOTOR_CONUTINE_SPEED_MAX_IOUT 5500

//空接抬升最大输出
#define LIFT_MOTOR_SPEED_MAX_OUT  6000
#define LIFT_MOTOR_SPEED_MAX_IOUT 3800
#define LIFT_MOTOR_ANGLE_MAX_OUT  450
#define LIFT_MOTOR_ANGLE_MAX_IOUT 400

//大小资源岛抬升最大输出
#define CASCADE_LIFT_MOTOR_SPEED_MAX_OUT 8000//6000
#define CASCADE_LIFT_MOTOR_SPEED_MAX_IOUT 6000//4000
#define CASCADE_LIFT_MOTOR_ANGLE_MAX_OUT  8000//6000
#define CASCADE_LIFT_MOTOR_ANGLE_MAX_IOUT  2000//540


//下落最大输出
#define DOWM_MOTOR_SPEED_MAX_OUT  6000
#define DOWN_MOTOR_SPEED_MAX_IOUT 2000

//最大YAW轴角度
#define MAX_YAW_ANGLE    120		
#define MIN_YAW_ANGLE   -120		


//取矿模式云台向右
#define YAW_ISLAND_ANGLE  -10.0f
#define PITCH_ISLAND_ANGLE -15.5f

//电流方向
#define PITCH_CURRENT_DIRECTION 1
#define YAW_CURRENT_DIRECTION   1

//鼠标控制云台灵敏度
#define PITCH_MOUSE_SEN 0.0001
#define YAW_MOUSE_SEN   0.0001

//鼠标控制运动转弯灵敏度
#define REMOTE_TURN_SENSITIVITY 1

//全速运动速度上限分界线
#define	Ahead_Speed 14000
#define	Back_Speed -14000

////真空泵状态
//#define PUMP_ON  1
//#define PUMP_OFF 0

//遥控器
#define RC_SW_UP                ((uint16_t)1)
#define RC_SW_MID               ((uint16_t)3)
#define RC_SW_DOWN              ((uint16_t)2)
#define switch_is_down(s)       (s == RC_SW_DOWN)
#define switch_is_mid(s)        (s == RC_SW_MID)
#define switch_is_up(s)         (s == RC_SW_UP)

//按下按键
#define IS_PRESSED 1
#define RELEASED    0

//刷卡两档目标值


#ifndef HELP_CARD_ANGLE_HERO
#define HELP_CARD_ANGLE_HERO Help_card_motor_start_angle+40

#else
#define HELP_CARD_ANGLE_INFANTRY          help_card_moto_start_angle+30
#define HELP_CARD_ANGLE_HERO_INFANTRY     help_card_moto_start_angle+36
#endif


//#define M3508_GIMBAL
#define DJ_GIMBAL_PITCH
#define MAITA_YAW

#ifdef DJ_GIMBAL_PITCH
	#define MAX_PITCH_PWM			1000
	#define MIN_PITCH_PWM			0
#endif

#ifdef MAITA_YAW
	#define ANGLE_AHEAD						28500
	#define ANGLE_MEDIUM					19500
	#define ANGLE_BACK						10500
#endif
enum
	{
		MOVE_NORMOL_SPEED			  = 0,
		MOVE_HIGH_SPEED		     =1,
		MOVE_SLOW_SPEED				=2,
	};
	
	enum
	{
		GIMBAL_MOVE_AHEAD			  = 0,
		GIMBAL_MOVE_BACK		=1		,
		GIMBAL_MEDIUM				=2 	,
	};

enum
	{
		GIMBAL_PITCH_UP			  = 0,
		GIMBAL_PITCH_MEDUIN		=1		,
		GIMBAL_PITCH_DOWN				=2 	,
	};	
enum
	{
		CHASSIS_NO_AUTO_MOVE			  = 0x00,
		CHASSIS_AUTO_LEFT	         	=0x01,
		CHASSIS_AUTO_RIGHT				=0x02 ,
		CHASSIS_AUTO_RIGHT_HIGH   =0x03,
	};
	
#endif