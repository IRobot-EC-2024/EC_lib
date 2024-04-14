/**
 * @Author       : Specific-Cola specificcola@proton.me
 * @Date         : 2024-03-22 23:03:00
 * @LastEditors  : H0pefu12 573341043@qq.com
 * @LastEditTime : 2024-04-12 14:09:53
 * @Description  :
 * @Filename     : struct_typedef.h
 * @       IRobot  EC_lib
 */
#ifndef STRUCT_TYPEDEF_H
#define STRUCT_TYPEDEF_H

#include <stdint.h>

#include "main.h"

typedef float fp32;
typedef double fp64;

typedef enum { FALSE = 0, TRUE = 1 } Bool_t;
typedef enum { RETURN_SUCCESS = 0, RETURN_ERROR = 1 } Return_t;
typedef enum { STATE_ONLINE = 0, STATE_OFFLINE = 1 } State_t;

#define NO RETURN_ERROR
#define OK RETURN_SUCCESS
#define bool_t Bool_t

typedef struct {
    fp32 YawAngle;
    fp32 PitchAngle;
    fp32 RollAngle;
    fp32 YawSpeed;
    fp32 PitchSpeed;
    fp32 RollSpeed;
} EulerSystemMeasure_t;

#endif
