#include "ws2812/ws2812.h"

#include <stdlib.h>
#include <string.h>

#define WS2812_SPI_0 0xC0
#define WS2812_SPI_1 0xF0
#define WS2812_SPI_RST 0xF0

static WS2812_t* ws2812_instance[MAX_WS2812_NUM];
static uint8_t id_cnt = 0;

WS2812_t* ws2812Add(WS2812_Register_t* reg) {
    WS2812_t* instance = (WS2812_t*)malloc(sizeof(WS2812_t));
    memset(instance, 0, sizeof(WS2812_t));

    instance->mode = reg->mode;
    instance->led_num = reg->led_num;
    if (reg->mode == WS2812_PWM) {
        PWM_Register_t pwm_reg;
        pwm_reg.htim = reg->pwm_reg.htim;
        pwm_reg.channel = reg->pwm_reg.channel;
        pwm_reg.period = 0.00125;
        pwm_reg.parent = instance;
        instance->pwm_device = pwmRegister(&pwm_reg);
    } else if (reg->mode == WS2812_SPI) {
        SPI_Register_t spi_reg;
        spi_reg.spi_handle = reg->spi_reg.hspi;
        spi_reg.parent = instance;
        instance->spi_device = spiRegister(&spi_reg);
    }

    instance->tx_buff = malloc(reg->led_num * RGB_BIT);
    memset(instance->tx_buff, 0, reg->led_num * RGB_BIT);

    ws2812_instance[id_cnt++] = instance;
    return instance;
}

void ws2812SetColor(WS2812_t* instance, uint8_t R, uint8_t G, uint8_t B, uint16_t num) {
    if (num >= instance->led_num) return;
    uint8_t i = 0, offset = num * (RGB_BIT);
    for (i = 0; i < 8; i++) {
        instance->tx_buff[offset + (7 - i)] = 0;
    }
}
