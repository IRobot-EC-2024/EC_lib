/**
 * @Author       : H0pefu12 573341043@qq.com
 * @Date         : 2024-02-29 22:03:35
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-08 23:42:20
 * @Description  :
 * @Filename     : Buzzer.h
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#ifndef BUZZER_H__
#define BUZZER_H__

#include "bsp_pwm.h"
#include "struct_typedef.h"

#define MAX_BUZZER_NUM 1  // 理论上C板应该只有一个蜂鸣器

typedef struct {
    PWM_Device_t* pwm;
    uint8_t* note;
    uint8_t* rhythm;
    uint8_t standard;
    fp32 volume;

} Buzzer_t;

typedef struct {
    TIM_HandleTypeDef* htim;  // TIM句柄
    uint32_t channel;         // 通道

} Buzzer_Register_t;

Buzzer_t* buzzerInit(Buzzer_Register_t* reg);
void buzzerOnce(Buzzer_t* buzzer);
void buzzerSeveralTimes(Buzzer_t* buzzer, uint8_t times, uint32_t duration_ms);
void buzzerSetTune(Buzzer_t* buzzer, uint32_t hz);
void buzzerSetVolume(Buzzer_t* buzzer, fp32 percent);

void buzzerSetMusicScore(Buzzer_t* buzzer, int16_t* score, uint32_t length,
                         uint16_t bpm, uint8_t standard);

#endif  // !BUZZER_H__
