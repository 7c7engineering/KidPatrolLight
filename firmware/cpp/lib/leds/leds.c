#include "leds.h"
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "gamma.h"

uint8_t leds_init() {
    PORTB.DIRSET = PIN2_bm | PIN1_bm | PIN0_bm; // Red, Green, Blue LEDs
    PORTA.DIRSET = PIN3_bm | PIN4_bm | PIN5_bm; // Red, Green, Blue LEDs


    // Invert the PINs so the PWM signal is active low
    PORTB.PIN2CTRL = PORT_INVEN_bm; //Red LED
    PORTB.PIN1CTRL = PORT_INVEN_bm; //Green LED
    PORTB.PIN0CTRL = PORT_INVEN_bm; //Blue LED
    PORTA.PIN3CTRL = PORT_INVEN_bm; //Red LED
    PORTA.PIN4CTRL = PORT_INVEN_bm; //Green LED
    PORTA.PIN5CTRL = PORT_INVEN_bm; //Blue LED

    TCA0.SPLIT.CTRLD = TCA_SPLIT_SPLITM_bm; // Split mode
    
    TCA0.SPLIT.CTRLB =   TCA_SPLIT_LCMP0EN_bm /* Enable Low Compare 0 */
                        | TCA_SPLIT_LCMP1EN_bm /* Enable Low Compare 1 */
                        | TCA_SPLIT_LCMP2EN_bm /* Enable Low Compare 2 */
                        | TCA_SPLIT_HCMP0EN_bm /* Enable High Compare 0 */
                        | TCA_SPLIT_HCMP1EN_bm /* Enable High Compare 1 */
                        | TCA_SPLIT_HCMP2EN_bm; /* Enable High Compare 2 */
    TCA0.SPLIT.CTRLC = 0x00;
    TCA0.SPLIT.LPER = 0xFF; // Set the period to 255 (8-bit resolution)
    TCA0.SPLIT.HPER = 0xFF; // Set the period to 255 (8-bit resolution)

    TCA0.SPLIT.CTRLA = TCA_SPLIT_ENABLE_bm /* Module Enable: enabled */;
    return 0;
}


void set_led_direct(uint8_t led, ledcolor_rgb_t color) {
    switch (led) {
        case 0:
            TCA0.SPLIT.HCMP0 = color.r;
            TCA0.SPLIT.HCMP1 = color.g;
            TCA0.SPLIT.HCMP2 = color.b;
            break;
        case 1:
            TCA0.SPLIT.LCMP0 = color.b;
            TCA0.SPLIT.LCMP1 = color.g;
            TCA0.SPLIT.LCMP2 = color.r;
            break;
        default:
            break;
    }
}

void set_led(uint8_t led, ledcolor_rgb_t color) {
    switch (led) {
        case 0:
            TCA0.SPLIT.HCMP0 = pgm_read_byte(&gamma_r[color.r]);
            TCA0.SPLIT.HCMP1 = pgm_read_byte(&gamma_g[color.g]);
            TCA0.SPLIT.HCMP2 = pgm_read_byte(&gamma_b[color.b]);
            break;
        case 1:
            TCA0.SPLIT.LCMP0 = pgm_read_byte(&gamma_b[color.b]);
            TCA0.SPLIT.LCMP1 = pgm_read_byte(&gamma_g[color.g]);
            TCA0.SPLIT.LCMP2 = pgm_read_byte(&gamma_r[color.r]);
            break;
        default:
            break;
    }
}