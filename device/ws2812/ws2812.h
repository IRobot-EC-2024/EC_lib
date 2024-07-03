#ifndef WS2812_H__
#define WS2812_H__

#include "bsp_pwm/bsp_pwm.h"
#include "bsp_spi/bsp_spi.h"
#include "struct_typedef.h"

#define MAX_WS2812_NUM 5  // WS2812灯条数目
#define RGB_BIT 24

typedef enum {
    WS2812_PWM,
    WS2812_SPI,
} WS2812_Mode_t;

typedef struct {
    WS2812_Mode_t mode;
    uint16_t led_num;
    uint8_t* tx_buff;
    union {
        PWM_Device_t* pwm_device;
        SPI_Device_t* spi_device;
    };

} WS2812_t;

typedef struct {
    WS2812_Mode_t mode;
    uint16_t led_num;
    union {
        struct {
            TIM_HandleTypeDef* htim;  // TIM句柄
            uint32_t channel;         // 通道
        } pwm_reg;

        struct {
            SPI_HandleTypeDef* hspi;
        } spi_reg;
    };

} WS2812_Register_t;

WS2812_t* ws2812Add(WS2812_Register_t* reg);

#endif  // !WS2812_H__
