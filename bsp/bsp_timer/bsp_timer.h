/**
 * @Author       : Specific-Cola specificcola@proton.me
 * @Date         : 2024-03-22 23:03:00
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-08 13:46:10
 * @Description  :
 * @Filename     : bsp_timer.h
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#ifndef BSP_TIMER_H__
#define BSP_TIMER_H__

#include "main.h"
#include "struct_typedef.h"
#include "tim.h"

#define TIMER_DEVICE_CNT 5  // 6,11,12,13,14
#define TIMER_FREQUENCY_MAX 1000000

typedef struct TIMER_Device_ {
    TIM_HandleTypeDef* htim;
    uint32_t tclk;  // 时钟频率
    uint32_t period;
    void (*timer_device_callback)(struct TIMER_Device_*);

    uint32_t period_cnt;  // 溢出次数

} Timer_Device_t;

typedef struct {
    TIM_HandleTypeDef* htim;
    uint32_t period;
    void (*timer_device_callback)(struct TIMER_Device_*);

} Timer_Register_t;

Timer_Device_t* timerDeviceRegister(Timer_Register_t* reg);
void timerOnActivate(Timer_Device_t* timer);
void timerOnDeactivate(Timer_Device_t* timer);
void timerSetPeriod(Timer_Device_t* timer, uint32_t period);
float timerGetDeltaTime(Timer_Device_t* timer, uint32_t* cnt_last);
#endif