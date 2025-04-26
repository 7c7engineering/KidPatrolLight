#include <stdint.h>
#include <avr/io.h>
#include "leds.h"

typedef struct
{
    ledcolor_rgb_t led1;
    ledcolor_rgb_t led2;
    int8_t ticks;
} animation_step_t;

// animation_step_t animation_safety_lights = {
//     {DIM_COLOR(COLOR_ORANGE, 37), DIM_COLOR(COLOR_ORANGE, 62), 1},
    

// }

animation_step_t animation_usa_police[] = {
    {COLOR_RED, COLOR_OFF,  2}, // red flash left
    {COLOR_OFF, COLOR_OFF,  2}, 
    {COLOR_RED, COLOR_OFF,  2}, // red flash left
    {COLOR_OFF, COLOR_OFF,  2},
    {COLOR_RED, COLOR_OFF,  2}, // red flash left
    {COLOR_OFF, COLOR_OFF,  2}, 
    {COLOR_RED, COLOR_OFF,  2}, // red flash left
    {COLOR_OFF, COLOR_OFF,  2}, 
    {COLOR_OFF, COLOR_BLUE, 2}, // blue flash right
    {COLOR_OFF, COLOR_OFF,  2}, 
    {COLOR_OFF, COLOR_BLUE, 2}, // blue flash right
    {COLOR_OFF, COLOR_OFF,  2},
    {COLOR_OFF, COLOR_BLUE, 2}, // blue flash right
    {COLOR_OFF, COLOR_OFF,  2}, 
    {COLOR_OFF, COLOR_BLUE, 2}, // blue flash right
    {COLOR_OFF, COLOR_OFF,  2},
    {COLOR_RED, COLOR_OFF,  2}, // red flash left
    {COLOR_OFF, COLOR_OFF,  2}, 
    {COLOR_RED, COLOR_OFF,  2}, // red flash left
    {COLOR_OFF, COLOR_OFF,  2},
    {COLOR_RED, COLOR_OFF,  2}, // red flash left
    {COLOR_OFF, COLOR_OFF,  2}, 
    {COLOR_RED, COLOR_OFF,  2}, // red flash left
    {COLOR_OFF, COLOR_OFF,  2}, 
    {COLOR_OFF, COLOR_BLUE, 2}, // blue flash right
    {COLOR_OFF, COLOR_OFF,  2}, 
    {COLOR_OFF, COLOR_BLUE, 2}, // blue flash right
    {COLOR_OFF, COLOR_OFF,  2},
    {COLOR_OFF, COLOR_BLUE, 2}, // blue flash right
    {COLOR_OFF, COLOR_OFF,  2}, 
    {COLOR_OFF, COLOR_BLUE, 2}, // blue flash right
    {COLOR_OFF, COLOR_OFF,  2},
    {COLOR_RED, COLOR_OFF,  25}, // long red left
    {COLOR_OFF, COLOR_BLUE, 25}, // long blue right
    {COLOR_RED, COLOR_OFF,  25}, // long red left
    {COLOR_OFF, COLOR_BLUE, 25}, // long blue right
    {{}, {}, -1} // End of animation
};