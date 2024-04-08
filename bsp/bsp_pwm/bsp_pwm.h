/**
 * @Author       : Specific-Cola specificcola@proton.me
 * @Date         : 2024-03-22 23:03:00
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-08 13:45:18
 * @Description  :
 * @Filename     : bsp_pwm.h
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#ifndef BSP_PWM_H__
#define BSP_PWM_H__

#include "struct_typedef.h"

#define PWM_DEVICE_CNT 16

typedef struct PWM_Device_ {
    TIM_HandleTypeDef* htim;                // TIM句柄
    uint32_t channel;                       // 通道
    uint32_t tclk;                          // 时钟频率
    float period;                           // 周期   单位毫秒
    float dutyratio;                        // 占空比
    void (*callback)(struct PWM_Device_*);  // DMA传输完成回调函数
    void* id;                               // 实例ID
} PWM_Device_t;

typedef struct {
    TIM_HandleTypeDef* htim;          // TIM句柄
    uint32_t channel;                 // 通道
    fp32 period;                      // 周期  单位毫秒
    float dutyratio;                  // 占空比
    void (*callback)(PWM_Device_t*);  // DMA传输完成回调函数
    void* id;                         // 实例ID
} PWM_Register_t;

PWM_Device_t* pwmRegister(PWM_Register_t* config);
void pwmOnActivate(PWM_Device_t* pwm);
void pwmOnDeactivate(PWM_Device_t* pwm);
void pwmSetDuty(PWM_Device_t* pwm, float dutyratio);
void pwmSetPeriod(PWM_Device_t* pwm, fp32 period);

#endif