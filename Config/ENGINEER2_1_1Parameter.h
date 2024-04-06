#ifndef __ENGINEER2_Parameter
#define __ENGINEER2_Parameter

// 兑换站前伸目标速度
#define EXCHANEG_PROTRACTION_SPEED 3000
#define EXCHANEG_PROTRACTION_SPEED_SLOWLY 600

// 初始前伸速度环pid参数
#define PROTRACTION_LEFT_MOTOR_SPEED_INIT_PID_KP 2  // 40
#define PROTRACTION_LEFT_MOTOR_SPEED_INIT_PID_KI 0  // 0.01
#define PROTRACTION_LEFT_MOTOR_SPEED_INIT_PID_KD 0

#define PROTRACTION_RIGHT_MOTOR_SPEED_INIT_PID_KP 2  // 40
#define PROTRACTION_RIGHT_MOTOR_SPEED_INIT_PID_KI 0  // 0.01
#define PROTRACTION_RIGHT_MOTOR_SPEED_INIT_PID_KD 0

// 初始前伸角度环pid参数
#define PROTRACTION_LEFT_MOTOR_ANGLE_INIT_PID_KP 30  // 28
#define PROTRACTION_LEFT_MOTOR_ANGLE_INIT_PID_KI 0   // 0.03
#define PROTRACTION_LEFT_MOTOR_ANGLE_INIT_PID_KD 0

#define PROTRACTION_RIGHT_MOTOR_ANGLE_INIT_PID_KP 30  // 28
#define PROTRACTION_RIGHT_MOTOR_ANGLE_INIT_PID_KI 0   // 0.03
#define PROTRACTION_RIGHT_MOTOR_ANGLE_INIT_PID_KD 0

// 前伸速度环pid参数
#define PROTRACTION_LEFT_MOTOR_SPEED_PID_KP 4  // 40
#define PROTRACTION_LEFT_MOTOR_SPEED_PID_KI 0  // 0.01
#define PROTRACTION_LEFT_MOTOR_SPEED_PID_KD 0

#define PROTRACTION_RIGHT_MOTOR_SPEED_PID_KP 4  // 40
#define PROTRACTION_RIGHT_MOTOR_SPEED_PID_KI 0  // 0.01
#define PROTRACTION_RIGHT_MOTOR_SPEED_PID_KD 0

// 前伸角度环pid参数
#define PROTRACTION_LEFT_MOTOR_ANGLE_PID_KP 30  // 28
#define PROTRACTION_LEFT_MOTOR_ANGLE_PID_KI 0   // 0.03
#define PROTRACTION_LEFT_MOTOR_ANGLE_PID_KD 0

#define PROTRACTION_RIGHT_MOTOR_ANGLE_PID_KP 30  // 28
#define PROTRACTION_RIGHT_MOTOR_ANGLE_PID_KI 0   // 0.03
#define PROTRACTION_RIGHT_MOTOR_ANGLE_PID_KD 0

// 前伸电机最大输出
#define PROTRACTION_MOTOR_SPEED_MAX_OUT 6000
#define PROTRACTION_MOTOR_SPEED_MAX_IOUT 4000
#define PROTRACTION_MOTOR_ANGLE_MAX_OUT 3000
#define PROTRACTION_MOTOR_ANGLE_MAX_IOUT 2000

// 前伸电机状态关节角度
#define PROTRACTION_JOINT_ANGLE_A_LITTLE_DISTANCE 40.0f

//---------------------------------------机械臂无载参数-----------------------------------------
// 机械臂关节0双环pid参数
#define ARM_MOTOR0_ANGLE_PID_KP 20
#define ARM_MOTOR0_ANGLE_PID_KI 0.005
#define ARM_MOTOR0_ANGLE_PID_KD 0
#define ARM_MOTOR0_SPEED_PID_KP 8
#define ARM_MOTOR0_SPEED_PID_KI 0
#define ARM_MOTOR0_SPEED_PID_KD 0

// 机械臂关节1双环pid参数
#define ARM_MOTOR1_ANGLE_PID_KP 15
#define ARM_MOTOR1_ANGLE_PID_KI 0.05
#define ARM_MOTOR1_ANGLE_PID_KD 0
#define ARM_MOTOR1_SPEED_PID_KP 6
#define ARM_MOTOR1_SPEED_PID_KI 0
#define ARM_MOTOR1_SPEED_PID_KD 0

// 机械臂关节2双环pid参数
#define ARM_MOTOR2_ANGLE_PID_KP 15
#define ARM_MOTOR2_ANGLE_PID_KI 0.05
#define ARM_MOTOR2_ANGLE_PID_KD 0
#define ARM_MOTOR2_SPEED_PID_KP 6
#define ARM_MOTOR2_SPEED_PID_KI 0
#define ARM_MOTOR2_SPEED_PID_KD 0

// 机械臂关节3双环pid参数
#define ARM_MOTOR3_ANGLE_PID_KP 20
#define ARM_MOTOR3_ANGLE_PID_KI 0.04
#define ARM_MOTOR3_ANGLE_PID_KD 0
#define ARM_MOTOR3_SPEED_PID_KP 6
#define ARM_MOTOR3_SPEED_PID_KI 0
#define ARM_MOTOR3_SPEED_PID_KD 0

// 机械臂关节4双环pid参数
#define ARM_MOTOR4_ANGLE_PID_KP 20
#define ARM_MOTOR4_ANGLE_PID_KI 0.02
#define ARM_MOTOR4_ANGLE_PID_KD 0
#define ARM_MOTOR4_SPEED_PID_KP 6
#define ARM_MOTOR4_SPEED_PID_KI 0
#define ARM_MOTOR4_SPEED_PID_KD 0

// 机械臂关节5双环pid参数
#define ARM_MOTOR5_ANGLE_PID_KP 20
#define ARM_MOTOR5_ANGLE_PID_KI 0.02
#define ARM_MOTOR5_ANGLE_PID_KD 0
#define ARM_MOTOR5_SPEED_PID_KP 6
#define ARM_MOTOR5_SPEED_PID_KI 0
#define ARM_MOTOR5_SPEED_PID_KD 0
//---------------------------------------机械臂无载参数-----------------------------------------

//---------------------------------------机械臂带载参数-----------------------------------------
// 机械臂关节0双环pid参数
#define ARM_MOTOR0_ANGLE_STRONG_PID_KP 20
#define ARM_MOTOR0_ANGLE_STRONG_PID_KI 0
#define ARM_MOTOR0_ANGLE_STRONG_PID_KD 0
#define ARM_MOTOR0_SPEED_STRONG_PID_KP 10
#define ARM_MOTOR0_SPEED_STRONG_PID_KI 0
#define ARM_MOTOR0_SPEED_STRONG_PID_KD 0

// 机械臂关节1双环pid参数
#define ARM_MOTOR1_ANGLE_STRONG_PID_KP 20
#define ARM_MOTOR1_ANGLE_STRONG_PID_KI 0.05
#define ARM_MOTOR1_ANGLE_STRONG_PID_KD 0
#define ARM_MOTOR1_SPEED_STRONG_PID_KP 6
#define ARM_MOTOR1_SPEED_STRONG_PID_KI 0
#define ARM_MOTOR1_SPEED_STRONG_PID_KD 0

// 机械臂关节2双环pid参数
#define ARM_MOTOR2_ANGLE_STRONG_PID_KP 20
#define ARM_MOTOR2_ANGLE_STRONG_PID_KI 0.05
#define ARM_MOTOR2_ANGLE_STRONG_PID_KD 0
#define ARM_MOTOR2_SPEED_STRONG_PID_KP 6
#define ARM_MOTOR2_SPEED_STRONG_PID_KI 0
#define ARM_MOTOR2_SPEED_STRONG_PID_KD 0

// 机械臂关节3双环pid参数
#define ARM_MOTOR3_ANGLE_STRONG_PID_KP 20
#define ARM_MOTOR3_ANGLE_STRONG_PID_KI 0.04
#define ARM_MOTOR3_ANGLE_STRONG_PID_KD 0
#define ARM_MOTOR3_SPEED_STRONG_PID_KP 6
#define ARM_MOTOR3_SPEED_STRONG_PID_KI 0
#define ARM_MOTOR3_SPEED_STRONG_PID_KD 0

// 机械臂关节4双环pid参数
#define ARM_MOTOR4_ANGLE_STRONG_PID_KP 18
#define ARM_MOTOR4_ANGLE_STRONG_PID_KI 0.01
#define ARM_MOTOR4_ANGLE_STRONG_PID_KD 0
#define ARM_MOTOR4_SPEED_STRONG_PID_KP 6
#define ARM_MOTOR4_SPEED_STRONG_PID_KI 0
#define ARM_MOTOR4_SPEED_STRONG_PID_KD 0

// 机械臂关节5双环pid参数
#define ARM_MOTOR5_ANGLE_STRONG_PID_KP 20
#define ARM_MOTOR5_ANGLE_STRONG_PID_KI 0.01
#define ARM_MOTOR5_ANGLE_STRONG_PID_KD 0
#define ARM_MOTOR5_SPEED_STRONG_PID_KP 6
#define ARM_MOTOR5_SPEED_STRONG_PID_KI 0
#define ARM_MOTOR5_SPEED_STRONG_PID_KD 0
//---------------------------------------机械臂带载参数-----------------------------------------

//---------------------------------------机械臂初始化参数-----------------------------------------
// 机械臂关节0双环pid参数
#define ARM_MOTOR0_ANGLE_INIT_PID_KP 15
#define ARM_MOTOR0_ANGLE_INIT_PID_KI 0
#define ARM_MOTOR0_ANGLE_INIT_PID_KD 0
#define ARM_MOTOR0_SPEED_INIT_PID_KP 6
#define ARM_MOTOR0_SPEED_INIT_PID_KI 0
#define ARM_MOTOR0_SPEED_INIT_PID_KD 0

// 机械臂关节1双环pid参数
#define ARM_MOTOR1_ANGLE_INIT_PID_KP 30
#define ARM_MOTOR1_ANGLE_INIT_PID_KI 0
#define ARM_MOTOR1_ANGLE_INIT_PID_KD 0
#define ARM_MOTOR1_SPEED_INIT_PID_KP 10
#define ARM_MOTOR1_SPEED_INIT_PID_KI 0
#define ARM_MOTOR1_SPEED_INIT_PID_KD 0

// 机械臂关节2双环pid参数
#define ARM_MOTOR2_ANGLE_INIT_PID_KP 20
#define ARM_MOTOR2_ANGLE_INIT_PID_KI 0
#define ARM_MOTOR2_ANGLE_INIT_PID_KD 0
#define ARM_MOTOR2_SPEED_INIT_PID_KP 8
#define ARM_MOTOR2_SPEED_INIT_PID_KI 0
#define ARM_MOTOR2_SPEED_INIT_PID_KD 0

// 机械臂关节3双环pid参数
#define ARM_MOTOR3_ANGLE_INIT_PID_KP 20
#define ARM_MOTOR3_ANGLE_INIT_PID_KI 0
#define ARM_MOTOR3_ANGLE_INIT_PID_KD 0
#define ARM_MOTOR3_SPEED_INIT_PID_KP 8
#define ARM_MOTOR3_SPEED_INIT_PID_KI 0
#define ARM_MOTOR3_SPEED_INIT_PID_KD 0

// 机械臂关节4双环pid参数
#define ARM_MOTOR4_ANGLE_INIT_PID_KP 18
#define ARM_MOTOR4_ANGLE_INIT_PID_KI 0
#define ARM_MOTOR4_ANGLE_INIT_PID_KD 0
#define ARM_MOTOR4_SPEED_INIT_PID_KP 6
#define ARM_MOTOR4_SPEED_INIT_PID_KI 0
#define ARM_MOTOR4_SPEED_INIT_PID_KD 0

// 机械臂关节5双环pid参数
#define ARM_MOTOR5_ANGLE_INIT_PID_KP 10
#define ARM_MOTOR5_ANGLE_INIT_PID_KI 0
#define ARM_MOTOR5_ANGLE_INIT_PID_KD 0
#define ARM_MOTOR5_SPEED_INIT_PID_KP 6
#define ARM_MOTOR5_SPEED_INIT_PID_KI 0
#define ARM_MOTOR5_SPEED_INIT_PID_KD 0
//---------------------------------------机械臂初始化参数-----------------------------------------

#define ARM_MOTOR0_SPEED_MAX_OUT M2006_MAX_OUTPUT
#define ARM_MOTOR0_SPEED_MAX_IOUT M2006_MAX_IOUTPUT
#define ARM_MOTOR1_SPEED_MAX_OUT M3508_MAX_OUTPUT
#define ARM_MOTOR1_SPEED_MAX_IOUT M3508_MAX_IOUTPUT
#define ARM_MOTOR2_SPEED_MAX_OUT M3508_MAX_OUTPUT
#define ARM_MOTOR2_SPEED_MAX_IOUT M3508_MAX_IOUTPUT
#define ARM_MOTOR3_SPEED_MAX_OUT M3508_MAX_OUTPUT
#define ARM_MOTOR3_SPEED_MAX_IOUT M3508_MAX_IOUTPUT
#define ARM_MOTOR4_SPEED_MAX_OUT M2006_MAX_OUTPUT
#define ARM_MOTOR4_SPEED_MAX_IOUT M2006_MAX_IOUTPUT
#define ARM_MOTOR5_SPEED_MAX_OUT M2006_MAX_OUTPUT
#define ARM_MOTOR5_SPEED_MAX_IOUT M2006_MAX_IOUTPUT

#define ARM_MOTOR0_ANGLE_MAX_OUT 4000.0
#define ARM_MOTOR0_ANGLE_MAX_IOUT 800.0
#define ARM_MOTOR1_ANGLE_MAX_OUT 2000.0
#define ARM_MOTOR1_ANGLE_MAX_IOUT 800.0
#define ARM_MOTOR2_ANGLE_MAX_OUT 3000.0
#define ARM_MOTOR2_ANGLE_MAX_IOUT 1000.0
#define ARM_MOTOR3_ANGLE_MAX_OUT 2000.0
#define ARM_MOTOR3_ANGLE_MAX_IOUT 400.0
#define ARM_MOTOR4_ANGLE_MAX_OUT 2000.0
#define ARM_MOTOR4_ANGLE_MAX_IOUT 800.0
#define ARM_MOTOR5_ANGLE_MAX_OUT 2000.0
#define ARM_MOTOR5_ANGLE_MAX_IOUT 800.0

#define ARM_MOTOR0_ANGLE_MAX 36000
#define ARM_MOTOR0_ANGLE_MIN -36000
#define ARM_MOTOR1_ANGLE_MAX 200
#define ARM_MOTOR1_ANGLE_MIN 20
#define ARM_MOTOR2_ANGLE_MAX 50
#define ARM_MOTOR2_ANGLE_MIN -60
#define ARM_MOTOR3_ANGLE_MAX 36000
#define ARM_MOTOR3_ANGLE_MIN -36000
#define ARM_MOTOR4_ANGLE_MAX 36000
#define ARM_MOTOR4_ANGLE_MIN -36000
#define ARM_MOTOR5_ANGLE_MAX 36000
#define ARM_MOTOR5_ANGLE_MIN -36000

//---------------------------------------银矿初始化参数-----------------------------------------
// 机械臂关节0双环pid参数
#define SILVER_MOTOR0_ANGLE_INIT_PID_KP 10
#define SILVER_MOTOR0_ANGLE_INIT_PID_KI 0
#define SILVER_MOTOR0_ANGLE_INIT_PID_KD 0
#define SILVER_MOTOR0_SPEED_INIT_PID_KP 5
#define SILVER_MOTOR0_SPEED_INIT_PID_KI 0
#define SILVER_MOTOR0_SPEED_INIT_PID_KD 0

// 机械臂关节1双环pid参数
#define SILVER_MOTOR1_ANGLE_INIT_PID_KP 15
#define SILVER_MOTOR1_ANGLE_INIT_PID_KI 0
#define SILVER_MOTOR1_ANGLE_INIT_PID_KD 0
#define SILVER_MOTOR1_SPEED_INIT_PID_KP 6
#define SILVER_MOTOR1_SPEED_INIT_PID_KI 0
#define SILVER_MOTOR1_SPEED_INIT_PID_KD 0

// 机械臂关节2双环pid参数
#define SILVER_MOTOR2_ANGLE_INIT_PID_KP 15
#define SILVER_MOTOR2_ANGLE_INIT_PID_KI 0
#define SILVER_MOTOR2_ANGLE_INIT_PID_KD 0
#define SILVER_MOTOR2_SPEED_INIT_PID_KP 6
#define SILVER_MOTOR2_SPEED_INIT_PID_KI 0
#define SILVER_MOTOR2_SPEED_INIT_PID_KD 0

// 机械臂关节3双环pid参数
#define SILVER_MOTOR3_ANGLE_INIT_PID_KP 15
#define SILVER_MOTOR3_ANGLE_INIT_PID_KI 0
#define SILVER_MOTOR3_ANGLE_INIT_PID_KD 0
#define SILVER_MOTOR3_SPEED_INIT_PID_KP 6
#define SILVER_MOTOR3_SPEED_INIT_PID_KI 0
#define SILVER_MOTOR3_SPEED_INIT_PID_KD 0

//---------------------------------------银矿初始化参数-----------------------------------------

//---------------------------------------银矿普通参数-----------------------------------------
// 机械臂关节0双环pid参数
#define SILVER_MOTOR0_ANGLE_PID_KP 10
#define SILVER_MOTOR0_ANGLE_PID_KI 0
#define SILVER_MOTOR0_ANGLE_PID_KD 0
#define SILVER_MOTOR0_SPEED_PID_KP 5
#define SILVER_MOTOR0_SPEED_PID_KI 0
#define SILVER_MOTOR0_SPEED_PID_KD 0

// 机械臂关节1双环pid参数
#define SILVER_MOTOR1_ANGLE_PID_KP 15
#define SILVER_MOTOR1_ANGLE_PID_KI 0
#define SILVER_MOTOR1_ANGLE_PID_KD 0
#define SILVER_MOTOR1_SPEED_PID_KP 6
#define SILVER_MOTOR1_SPEED_PID_KI 0
#define SILVER_MOTOR1_SPEED_PID_KD 0

// 机械臂关节2双环pid参数
#define SILVER_MOTOR2_ANGLE_PID_KP 15
#define SILVER_MOTOR2_ANGLE_PID_KI 0
#define SILVER_MOTOR2_ANGLE_PID_KD 0
#define SILVER_MOTOR2_SPEED_PID_KP 6
#define SILVER_MOTOR2_SPEED_PID_KI 0
#define SILVER_MOTOR2_SPEED_PID_KD 0

// 机械臂关节3双环pid参数
#define SILVER_MOTOR3_ANGLE_PID_KP 15
#define SILVER_MOTOR3_ANGLE_PID_KI 0
#define SILVER_MOTOR3_ANGLE_PID_KD 0
#define SILVER_MOTOR3_SPEED_PID_KP 6
#define SILVER_MOTOR3_SPEED_PID_KI 0
#define SILVER_MOTOR3_SPEED_PID_KD 0

//---------------------------------------银矿普通参数-----------------------------------------

//---------------------------------------金矿初始化参数-----------------------------------------
// 机械臂关节0双环pid参数
#define GOLD_MOTOR0_ANGLE_INIT_PID_KP 15
#define GOLD_MOTOR0_ANGLE_INIT_PID_KI 0
#define GOLD_MOTOR0_ANGLE_INIT_PID_KD 0
#define GOLD_MOTOR0_SPEED_INIT_PID_KP 6
#define GOLD_MOTOR0_SPEED_INIT_PID_KI 0
#define GOLD_MOTOR0_SPEED_INIT_PID_KD 0

// 机械臂关节1双环pid参数
#define GOLD_MOTOR1_ANGLE_INIT_PID_KP 15
#define GOLD_MOTOR1_ANGLE_INIT_PID_KI 0
#define GOLD_MOTOR1_ANGLE_INIT_PID_KD 0
#define GOLD_MOTOR1_SPEED_INIT_PID_KP 6
#define GOLD_MOTOR1_SPEED_INIT_PID_KI 0
#define GOLD_MOTOR1_SPEED_INIT_PID_KD 0

// 机械臂关节2双环pid参数
#define GOLD_MOTOR2_ANGLE_INIT_PID_KP 15
#define GOLD_MOTOR2_ANGLE_INIT_PID_KI 0
#define GOLD_MOTOR2_ANGLE_INIT_PID_KD 0
#define GOLD_MOTOR2_SPEED_INIT_PID_KP 6
#define GOLD_MOTOR2_SPEED_INIT_PID_KI 0
#define GOLD_MOTOR2_SPEED_INIT_PID_KD 0

// 机械臂关节3双环pid参数
#define GOLD_MOTOR3_ANGLE_INIT_PID_KP 15
#define GOLD_MOTOR3_ANGLE_INIT_PID_KI 0
#define GOLD_MOTOR3_ANGLE_INIT_PID_KD 0
#define GOLD_MOTOR3_SPEED_INIT_PID_KP 6
#define GOLD_MOTOR3_SPEED_INIT_PID_KI 0
#define GOLD_MOTOR3_SPEED_INIT_PID_KD 0

//---------------------------------------金矿初始化参数-----------------------------------------

//---------------------------------------金矿普通参数-----------------------------------------
// 机械臂关节0双环pid参数
#define GOLD_MOTOR0_ANGLE_PID_KP 15
#define GOLD_MOTOR0_ANGLE_PID_KI 0
#define GOLD_MOTOR0_ANGLE_PID_KD 0
#define GOLD_MOTOR0_SPEED_PID_KP 6
#define GOLD_MOTOR0_SPEED_PID_KI 0
#define GOLD_MOTOR0_SPEED_PID_KD 0

// 机械臂关节1双环pid参数
#define GOLD_MOTOR1_ANGLE_PID_KP 15
#define GOLD_MOTOR1_ANGLE_PID_KI 0
#define GOLD_MOTOR1_ANGLE_PID_KD 0
#define GOLD_MOTOR1_SPEED_PID_KP 6
#define GOLD_MOTOR1_SPEED_PID_KI 0
#define GOLD_MOTOR1_SPEED_PID_KD 0

// 机械臂关节2双环pid参数
#define GOLD_MOTOR2_ANGLE_PID_KP 15
#define GOLD_MOTOR2_ANGLE_PID_KI 0
#define GOLD_MOTOR2_ANGLE_PID_KD 0
#define GOLD_MOTOR2_SPEED_PID_KP 6
#define GOLD_MOTOR2_SPEED_PID_KI 0
#define GOLD_MOTOR2_SPEED_PID_KD 0

// 机械臂关节3双环pid参数
#define GOLD_MOTOR3_ANGLE_PID_KP 15
#define GOLD_MOTOR3_ANGLE_PID_KI 0
#define GOLD_MOTOR3_ANGLE_PID_KD 0
#define GOLD_MOTOR3_SPEED_PID_KP 6
#define GOLD_MOTOR3_SPEED_PID_KI 0
#define GOLD_MOTOR3_SPEED_PID_KD 0

//---------------------------------------金矿普通参数-----------------------------------------

// 真空泵状态
#define PUMP_ON 1
#define PUMP_OFF 0
#define PUMP1_OFFSET (1 << 0)
#define PUMP2_OFFSET (1 << 1)
#define PUMP3_OFFSET (1 << 2)
#define PUMP4_OFFSET (1 << 3)

// 位置环到达目标位置死区
#define REACH_BAND 12

// 存在模式转换
#define TRANSLATION 1

// 自动对位模式
#define ALIGNMENT_MODE 1

// 定义长按时间
#define LONG_PRESSED_TIME 1000

// 定义吸盘形成真空所需时间
#define VACUUM_TIME 1000

#define EXCHANGE_STATION 4

#define YAW_MEDIUM_ANGLE 0.5f

#endif
