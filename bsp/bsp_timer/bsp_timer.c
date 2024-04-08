/**
 * @Author       : Specific-Cola specificcola@proton.me
 * @Date         : 2024-03-22 23:03:00
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-08 13:45:58
 * @Description  :
 * @Filename     : bsp_timer.c
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#include "bsp_timer.h"

#include <stdlib.h>

static Timer_Device_t* timer_device[TIMER_DEVICE_CNT] = {NULL};
static uint8_t id_cnt = 0;
static uint32_t timerSelectTclk(TIM_HandleTypeDef* htim);

#if defined(STM32F407xx) || defined(STM32F427xx)
#define PCLK1_MULT                                                          \
    (APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos] == 0 \
         ? 1                                                                \
         : 2)
#define PCLK2_MULT                                                          \
    (APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos] == 0 \
         ? 1                                                                \
         : 2)
#elif defined(STM32H723xx)
#define PCLK1_MULT                                          \
    (D1CorePrescTable[(RCC->D2CFGR & RCC_D2CFGR_D2PPRE1) >> \
                      RCC_D2CFGR_D2PPRE1_Pos] == 0          \
         ? 1                                                \
         : 2)
#define PCLK2_MULT                                          \
    (D1CorePrescTable[(RCC->D2CFGR & RCC_D2CFGR_D2PPRE2) >> \
                      RCC_D2CFGR_D2PPRE2_Pos] == 0          \
         ? 1                                                \
         : 2)
#endif

static uint32_t timerSelectTclk(TIM_HandleTypeDef* htim) {
    uintptr_t tclk_temp = ((uintptr_t)((htim)->Instance));
    if ((tclk_temp <= (APB1PERIPH_BASE + 0x2000UL)) &&
        (tclk_temp >= (APB1PERIPH_BASE + 0x0000UL))) {
        return (HAL_RCC_GetPCLK1Freq() * PCLK1_MULT);
    } else if (((tclk_temp <= (APB2PERIPH_BASE + 0x0400UL)) &&
                (tclk_temp >= (APB2PERIPH_BASE + 0x0000UL))) ||
               ((tclk_temp <= (APB2PERIPH_BASE + 0x4800UL)) &&
                (tclk_temp >= (APB2PERIPH_BASE + 0x4000UL)))) {
        return (HAL_RCC_GetPCLK2Freq() * PCLK2_MULT);
    }
    return 0;
}

Timer_Device_t* timerDeviceRegister(Timer_Register_t* reg) {
    if (id_cnt > TIMER_DEVICE_CNT) {
        Error_Handler();  // 后面希望定义一个全局变量来展示错误类型
    }

    for (uint8_t i = 0; i < id_cnt; i++) {
        if (timer_device[i]->htim == reg->htim) {
            Error_Handler();
        }
    }

    Timer_Device_t* instance = (Timer_Device_t*)malloc(sizeof(Timer_Device_t));

    instance->htim = reg->htim;
    instance->timer_device_callback = reg->timer_device_callback;
    instance->tclk = timerSelectTclk(reg->htim);
    instance->period = reg->period;

    __HAL_TIM_SET_PRESCALER(instance->htim,
                            instance->tclk / TIMER_FREQUENCY_MAX - 1);
    timerSetPeriod(instance, instance->period);
    __HAL_TIM_ENABLE_IT(instance->htim, TIM_IT_UPDATE);

    timer_device[id_cnt++] = instance;
    timerOnActivate(instance);

    return instance;
}

void timerSetPeriod(Timer_Device_t* timer, uint32_t period) {
    __HAL_TIM_SetAutoreload(timer->htim, period);  // 单位是us
}

void timerOnActivate(Timer_Device_t* timer) {
    HAL_TIM_Base_Start(timer->htim);
    HAL_TIM_Base_Start_IT(timer->htim);
    return;
}
void timerOnDeactivate(Timer_Device_t* timer) {
    HAL_TIM_Base_Stop_IT(timer->htim);
    return;
}

float timerGetDeltaTime(Timer_Device_t* timer, uint32_t* cnt_last) {
    volatile uint32_t cnt_now = __HAL_TIM_GET_COUNTER(timer->htim);
    uint32_t arr = __HAL_TIM_GetAutoreload(timer->htim);
    float dt = ((uint32_t)(cnt_now + timer->period_cnt * arr - *cnt_last)) /
               ((float)(TIMER_FREQUENCY_MAX));
    *cnt_last = cnt_now + timer->period_cnt * arr;

    return dt;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    if (htim->Instance == TIM7) {
        HAL_IncTick();
        return;
    }

    uint8_t i = 0;
    for (i = 0; i < id_cnt; i++) {
        if (timer_device[i]->htim == htim) {
            if (timer_device[i]->timer_device_callback != NULL)
                timer_device[i]->timer_device_callback(timer_device[i]);
            timer_device[i]->period_cnt++;
            break;
        }
    }
}
