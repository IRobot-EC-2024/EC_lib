#ifndef __ENGINEER2_Parameter
#define __ENGINEER2_Parameter

/*磁编码器返回数据结构体*/
#ifndef __EncoderAs5600
// #define __EncoderAs5600
#define ENCODER_UP 0.00f
#define ENCODER_FORWARD 90.00f
#define ENCODER_DOWN 180.00f
#define ENCODER_BACK 270.00f
#define ENCODER_UP_FORWARD 45.00f
#endif

#define IMU_UP 0.123445f
#define IMU_FORWARD -81.5625f
#define IMU_BACK 80.892334f

// 翻转和前伸时间间隔
#define SPIN_PROTRACTION_TIME 1200

// 翻转速度
#define SPIN_SPEED 2500
#define SPIN_SPEED_SLOWLY 500
// 伸到最远目标速度
#define FAREST_SPEED 6000    // 4500
#define BACK_AIR_SPEED 6000  // 4500

// 兑换站前伸目标速度
#define EXCHANEG_PROTRACTION_SPEED 3000
#define EXCHANEG_PROTRACTION_SPEED_SLOWLY 600
// 无矿石时翻转速度环pid参数
#define SPIN_MOTOR_SPEED_PID_KP 5  // 2
#define SPIN_MOTOR_SPEED_PID_KI 0  // 0.02
#define SPIN_MOTOR_SPEED_PID_KD 0

// 无矿石时翻转角度环pid参数
#define SPIN_MOTOR_ANGLE_PID_KP 30  // 45
#define SPIN_MOTOR_ANGLE_PID_KI 0.05
#define SPIN_MOTOR_ANGLE_PID_KD 0

// 翻转停止pid
#define SPIN_MOTOR_STOP_PID_KP 35    // 35
#define SPIN_MOTOR_STOP_PID_KI 0.05  // 0.05f
#define SPIN_MOTOR_STOP_PID_KD 0

// 有矿石时翻转速度控制pid参数
#define SPIN_MOTOR_SPEED_CONTROLL_WITH_MINE_KP 30  //
#define SPIN_MOTOR_SPEED_CONTROLL_WITH_MINE_KI 0
#define SPIN_MOTOR_SPEED_CONTROLL_WITH_MINE_KD 0

// 有矿石时翻转速度环pid参数
#define SPIN_MOTOR_SPEED_WITH_MINE_KP 15  //
#define SPIN_MOTOR_SPEED_WITH_MINE_KI 0
#define SPIN_MOTOR_SPEED_WITH_MINE_KD 0

// 有矿石时翻转角度环pid参数
#define SPIN_MOTOR_ANGLE_WITH_MINE_KP 50  // 60
#define SPIN_MOTOR_ANGLE_WITH_MINE_KI 0
#define SPIN_MOTOR_ANGLE_WITH_MINE_KD 0

// 调姿电机速度环参数
#define VECTOR_MOTOR_SPEED_PID_KP 20
#define VECTOR_MOTOR_SPEED_PID_KI 0
#define VECTOR_MOTOR_SPEED_PID_KD 0

// 调姿电机速度环参数
#define VECTOR_MOTOR_STOP_SPEED_PID_KP 30
#define VECTOR_MOTOR_STOP_SPEED_PID_KI 0
#define VECTOR_MOTOR_STOP_SPEED_PID_KD 0

// 初始前伸速度环pid参数
#define PROTRACTION_LEFT_MOTOR_SPEED_INIT_PID_KP 6  // 40
#define PROTRACTION_LEFT_MOTOR_SPEED_INIT_PID_KI 0  // 0.01
#define PROTRACTION_LEFT_MOTOR_SPEED_INIT_PID_KD 0

#define PROTRACTION_RIGHT_MOTOR_SPEED_INIT_PID_KP 6  // 40
#define PROTRACTION_RIGHT_MOTOR_SPEED_INIT_PID_KI 0  // 0.01
#define PROTRACTION_RIGHT_MOTOR_SPEED_INIT_PID_KD 0

// 初始前伸角度环pid参数
#define PROTRACTION_LEFT_MOTOR_ANGLE_INIT_PID_KP 26  // 28
#define PROTRACTION_LEFT_MOTOR_ANGLE_INIT_PID_KI 0   // 0.03
#define PROTRACTION_LEFT_MOTOR_ANGLE_INIT_PID_KD 0

#define PROTRACTION_RIGHT_MOTOR_ANGLE_INIT_PID_KP 26  // 28
#define PROTRACTION_RIGHT_MOTOR_ANGLE_INIT_PID_KI 0   // 0.03
#define PROTRACTION_RIGHT_MOTOR_ANGLE_INIT_PID_KD 0

// 前伸速度环pid参数
#define PROTRACTION_LEFT_MOTOR_SPEED_PID_KP 8.0f  // 40
#define PROTRACTION_LEFT_MOTOR_SPEED_PID_KI 0.0f  // 0.01
#define PROTRACTION_LEFT_MOTOR_SPEED_PID_KD 0.0f

#define PROTRACTION_RIGHT_MOTOR_SPEED_PID_KP 8.0f  // 40
#define PROTRACTION_RIGHT_MOTOR_SPEED_PID_KI 0.0f  // 0.01
#define PROTRACTION_RIGHT_MOTOR_SPEED_PID_KD 0.0f

// 前伸角度环pid参数
#define PROTRACTION_LEFT_MOTOR_ANGLE_PID_KP 35.0f  // 28
#define PROTRACTION_LEFT_MOTOR_ANGLE_PID_KI 0.0f   // 0.03
#define PROTRACTION_LEFT_MOTOR_ANGLE_PID_KD 0.0f

#define PROTRACTION_RIGHT_MOTOR_ANGLE_PID_KP 35.0f  // 28
#define PROTRACTION_RIGHT_MOTOR_ANGLE_PID_KI 0.0f   // 0.03
#define PROTRACTION_RIGHT_MOTOR_ANGLE_PID_KD 0.0f

// 大资源岛前伸速度环pid参数
#define BIG_LEFT_PROTRACTION_MOTOR_SPEED_PID_KP 8  // 40
#define BIG_LEFT_PROTRACTION_MOTOR_SPEED_PID_KI 0  // 0.01
#define BIG_LEFT_PROTRACTION_MOTOR_SPEED_PID_KD 0

#define BIG_RIGHT_PROTRACTION_MOTOR_SPEED_PID_KP 8  // 40
#define BIG_RIGHT_PROTRACTION_MOTOR_SPEED_PID_KI 0  // 0.01
#define BIG_RIGHT_PROTRACTION_MOTOR_SPEED_PID_KD 0

// 大资源岛前伸角度环pid参数
#define BIG_LEFT_PROTRACTION_MOTOR_ANGLE_PID_KP 35  // 25
#define BIG_LEFT_PROTRACTION_MOTOR_ANGLE_PID_KI 0
#define BIG_LEFT_PROTRACTION_MOTOR_ANGLE_PID_KD 0.02

#define BIG_RIGHT_PROTRACTION_MOTOR_ANGLE_PID_KP 35  // 25
#define BIG_RIGHT_PROTRACTION_MOTOR_ANGLE_PID_KI 0
#define BIG_RIGHT_PROTRACTION_MOTOR_ANGLE_PID_KD 0.02

// 小资源岛前伸速度环pid参数
#define LITTLE_LEFT_PROTRACTION_MOTOR_SPEED_PID_KP 10  // 15
#define LITTLE_LEFT_PROTRACTION_MOTOR_SPEED_PID_KI 0   // 0.01
#define LITTLE_LEFT_PROTRACTION_MOTOR_SPEED_PID_KD 0

#define LITTLE_RIGHT_PROTRACTION_MOTOR_SPEED_PID_KP 10  // 15
#define LITTLE_RIGHT_PROTRACTION_MOTOR_SPEED_PID_KI 0   // 0.01
#define LITTLE_RIGHT_PROTRACTION_MOTOR_SPEED_PID_KD 0

// 小资源岛前伸角度环pid参数
#define LITTLE_LEFT_PROTRACTION_MOTOR_ANGLE_PID_KP 30
#define LITTLE_LEFT_PROTRACTION_MOTOR_ANGLE_PID_KI 0.01
#define LITTLE_LEFT_PROTRACTION_MOTOR_ANGLE_PID_KD 0

#define LITTLE_RIGHT_PROTRACTION_MOTOR_ANGLE_PID_KP 30
#define LITTLE_RIGHT_PROTRACTION_MOTOR_ANGLE_PID_KI 0
#define LITTLE_RIGHT_PROTRACTION_MOTOR_ANGLE_PID_KD 0

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
#define ARM_MOTOR1_SPEED_PID_KP 150
#define ARM_MOTOR1_SPEED_PID_KI 0
#define ARM_MOTOR1_SPEED_PID_KD 0

// 机械臂关节2双环pid参数
#define ARM_MOTOR2_ANGLE_PID_KP 15
#define ARM_MOTOR2_ANGLE_PID_KI 0.05
#define ARM_MOTOR2_ANGLE_PID_KD 0
#define ARM_MOTOR2_SPEED_PID_KP 0.003
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
#define ARM_MOTOR1_SPEED_STRONG_PID_KP 200
#define ARM_MOTOR1_SPEED_STRONG_PID_KI 0
#define ARM_MOTOR1_SPEED_STRONG_PID_KD 0

// 机械臂关节2双环pid参数
#define ARM_MOTOR2_ANGLE_STRONG_PID_KP 25
#define ARM_MOTOR2_ANGLE_STRONG_PID_KI 0.05
#define ARM_MOTOR2_ANGLE_STRONG_PID_KD 0
#define ARM_MOTOR2_SPEED_STRONG_PID_KP 0.003
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
#define ARM_MOTOR1_ANGLE_INIT_PID_KP 15
#define ARM_MOTOR1_ANGLE_INIT_PID_KI 0
#define ARM_MOTOR1_ANGLE_INIT_PID_KD 0
#define ARM_MOTOR1_SPEED_INIT_PID_KP 200
#define ARM_MOTOR1_SPEED_INIT_PID_KI 0
#define ARM_MOTOR1_SPEED_INIT_PID_KD 0

// 机械臂关节2双环pid参数
#define ARM_MOTOR2_ANGLE_INIT_PID_KP 15
#define ARM_MOTOR2_ANGLE_INIT_PID_KI 0
#define ARM_MOTOR2_ANGLE_INIT_PID_KD 0
#define ARM_MOTOR2_SPEED_INIT_PID_KP 0.003
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
#define ARM_MOTOR1_SPEED_MAX_OUT GM6020_MAX_OUTPUT
#define ARM_MOTOR1_SPEED_MAX_IOUT GM6020_MAX_IOUTPUT
#define ARM_MOTOR2_SPEED_MAX_OUT 4
#define ARM_MOTOR2_SPEED_MAX_IOUT 0.1
#define ARM_MOTOR3_SPEED_MAX_OUT M2006_MAX_OUTPUT
#define ARM_MOTOR3_SPEED_MAX_IOUT M2006_MAX_IOUTPUT
#define ARM_MOTOR4_SPEED_MAX_OUT M2006_MAX_OUTPUT
#define ARM_MOTOR4_SPEED_MAX_IOUT M2006_MAX_IOUTPUT
#define ARM_MOTOR5_SPEED_MAX_OUT M2006_MAX_OUTPUT
#define ARM_MOTOR5_SPEED_MAX_IOUT M2006_MAX_IOUTPUT

#define ARM_MOTOR0_ANGLE_MAX_OUT 2000.0
#define ARM_MOTOR0_ANGLE_MAX_IOUT 800.0
#define ARM_MOTOR1_ANGLE_MAX_OUT 200.0
#define ARM_MOTOR1_ANGLE_MAX_IOUT 50.0
#define ARM_MOTOR2_ANGLE_MAX_OUT 3000.0
#define ARM_MOTOR2_ANGLE_MAX_IOUT 1000.0
#define ARM_MOTOR3_ANGLE_MAX_OUT 1200.0
#define ARM_MOTOR3_ANGLE_MAX_IOUT 400.0
#define ARM_MOTOR4_ANGLE_MAX_OUT 2000.0
#define ARM_MOTOR4_ANGLE_MAX_IOUT 800.0
#define ARM_MOTOR5_ANGLE_MAX_OUT 2000.0
#define ARM_MOTOR5_ANGLE_MAX_IOUT 800.0

// 前伸电机最大输出
#define PROTRACTION_MOTOR_SPEED_MAX_OUT 6000
#define PROTRACTION_MOTOR_SPEED_MAX_IOUT 4000
#define PROTRACTION_MOTOR_ANGLE_MAX_OUT 3000
#define PROTRACTION_MOTOR_ANGLE_MAX_IOUT 2000

// 调姿电机最大输出
#define VECTOR_MOTOR_SPEED_MAX_OUT 8000
#define VECTOR_MOTOR_SPEED_MAX_IOUT 2000

#define VECTOR_MOTOR_STOP_SPEED_MAX_OUT 8000
#define VECTOR_MOTOR_STOP_SPEED_MAX_IOUT 3000

// 真空泵状态
#define PUMP_ON 1
#define PUMP_OFF 0

// 位置环到达目标位置死区
#define REACH_BAND 12

// 存在模式转换
#define TRANSLATION 1

// 翻转电机目标位置 上、前、下、后
// #ifdef IMU_ANGLE_CONTROL
// #define IMU_UP   0.07578125f
// #define IMU_FORWARD -84.5402832f
// #define IMU_FORWARD_UP -37.3754883f
// #define IMU_BACK   84.9737549f
// #endif
// 翻转电机上下前后
#define SPIN_UPWARD 217.0f
#define SPIN_FORWARD 125.0f
#define SPIN_DOWNWARD 34.0f
#define SPIN_BACKWARD 307.0f
#define SPIN_UP_BACK 255.0f

#define SPIN_FORWARD_SPEED -2400
#define SPIN_BACKWARD_SPEED 2400

// 翻转电机电流方向
#define SPIN_CURRENT_DIRECTION 1

// 翻转电机最大输出
#define MAX_PITCH_ANGLE_WITHOUT_MINE_OUT 4000.0f
#define MAX_PITCH_ANGLE_WITHOUT_MINE_IOUT 3000.0f

#define MAX_PITCH_SPEED_WITHOUT_MINE_OUT 4000.0f
#define MAX_PITCH_SPEED_WITHOUT_MINE_IOUT 3000.0f

#define MAX_PITCH_STOP_WITHOUT_MINE_OUT 4000.0f
#define MAX_PITCH_STOP_WITHOUT_MINE_IOUT 3000.0f

#define MAX_PITCH_STOP_WITH_MINE_OUT 12000.0f  // 15000.0f
#define MAX_PITCH_STOP_WITH_MINE_IOUT 4000.0f  // 5000.0f

#define MAX_PITCH_ANGLE_WITH_MINE_OUT 4000.0f   // 6000.0f
#define MAX_PITCH_ANGLE_WITH_MINE_IOUT 2000.0f  // 3000.0f

#define MAX_PITCH_SPEED_WITH_MINE_OUT 8000
#define MAX_PITCH_SPEED_WITH_MINE_IOUT 3000

#define MAX_PITCH_SPEED_CONTROLL_WITH_MINE_OUT 6000
#define MAX_PITCH_SPEED_CONTROLL_WITH_MINE_IOUT 3000

// pitch角度绝对限幅
#define MAX_ANGLE 50.0
#define MIN_ANGLE -50.0

// 自动对位模式
#define ALIGNMENT_MODE 1

// 定义长按时间
#define LONG_PRESSED_TIME 1000

// 定义吸盘形成真空所需时间
#define VACUUM_TIME 1000

// 调姿速度
#define CHANGE_MINE_SPEED 2500
#define CHANGE_MINE_SPEED_QUICKLY 6000           // 6000
#define CHANGE_MINE_SPEED_QUICKLY_EXCHNAGE 6000  // 6000
#define CHANGE_MINE_SPEED_SLOWLY 500             // 500
#define CHANGE_MINE_SPEED_MEDIUMLY 4000
#define CHANGE_MINE_STOP_LIFT_SPEED 5
// 存矿抬升时间
#define SAVE_MINE_LIFT_TIME 800

#define EXCHANGE_STATION 4

#define YAW_MEDIUM_ANGLE 0.5f

#endif