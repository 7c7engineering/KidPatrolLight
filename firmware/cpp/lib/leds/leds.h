#pragma once

#include "stdint.h"
#include "avr/io.h"



typedef struct ledcolor_rgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} ledcolor_rgb_t;


typedef struct ledcolor_hsl {
    uint8_t h;
    uint8_t s;
    uint8_t l;
} ledcolor_hsl_t;

#define COLOR_OFF    (ledcolor_rgb_t){0,  0,  0 }
#define COLOR_RED    (ledcolor_rgb_t){63, 0,  0 }
#define COLOR_GREEN  (ledcolor_rgb_t){0,  63, 0 }
#define COLOR_BLUE   (ledcolor_rgb_t){0,  0,  63}
#define COLOR_ORANGE (ledcolor_rgb_t){63, 63, 0}

uint8_t leds_init();
void set_led(uint8_t led, ledcolor_rgb_t color);
void set_led_direct(uint8_t led, ledcolor_rgb_t color);

#define DIM_COLOR(color, dim) (ledcolor_rgb_t){(color.r * dim) / 63, (color.g * dim) / 63, (color.b * dim) / 63}

// LED LEDR1 = PB2
#define PORT_LEDR1 PORTB
#define PIN_LEDR1 PIN2_bp
// LED LEDG1 = PB1
#define PORT_LEDG1 PORTB
#define PIN_LEDG1 PIN1_bp
// LED LEDB1 = PB0
#define PORT_LEDB1 PORTB
#define PIN_LEDB1 PIN0_bp

// LED LEDR2 = PA0
#define PORT_LEDR2 PORTA
#define PIN_LEDR2 PIN0_bp
// LED LEDG2 = PA1
#define PORT_LEDG2 PORTA
#define PIN_LEDG2 PIN1_bp
// LED LEDB2 = PA2
#define PORT_LEDB2 PORTA
#define PIN_LEDB2 PIN2_bp