/**
 * @Author       : Specific_Cola specificcola@proton.me
 * @Date         : 2024-03-22 23:03:00
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-08 13:42:19
 * @Description  :
 * @Filename     : bsp_delay.h
 * @Copyright (c) 2024 by IRobot, All Rights Reserved.
 * @
 */
#ifndef BSP_DELAY_H__
#define BSP_DELAY_H__
#include "struct_typedef.h"

extern void delayInit(void);
extern void delayUs(uint32_t nus);
extern void delayMs(uint16_t nms);
#endif
