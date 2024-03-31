#ifndef STRUCT_TYPEDEF_H
#define STRUCT_TYPEDEF_H

#include "main.h"
#include "stdint.h"

typedef float fp32;
typedef double fp64;

typedef enum{
    FALSE=0   ,
    TRUE=1
}Bool_t;
typedef enum{
    OK=0,  
    NO=1
}Return_t;
enum{
    ONLINE = 0,
    OFFLINE = 1
};

#define RETURN_ERROR    NO
#define RETURN_SUCCESS  OK
#define bool_t          Bool_t

typedef struct{
    fp32    YawAngle;
    fp32    PitchAngle;
    fp32    RollAngle;
    fp32    YawSpeed;
    fp32    PitchSpeed;
    fp32    RollSpeed;
} EulerSystemMeasure_t;

#endif



