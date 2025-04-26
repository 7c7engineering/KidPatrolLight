#include "stdint.h"
#include "avr/io.h"
#include "leds.h"
#include <avr/interrupt.h>

#define F_CPU 10000000UL
#include <util/delay.h>
#include "animations.h"

#include "math.h"

#define SECONDS_BEFORE_SLEEP 120

static volatile uint16_t overflow_count = 0; // Overflow count for RTC
static volatile uint8_t led_state = 0;       // State of the LED
static volatile uint8_t current_animation = 0;
static volatile int8_t animation_ticks_left = 0;
static volatile uint8_t animation_step = 0;

void do_animation_tick()
{
    if(animation_ticks_left == 0)
    {
        animation_step++;
        animation_ticks_left = animation_usa_police[animation_step].ticks;
        if(animation_usa_police[animation_step].ticks == -1)
        {
            animation_step = 0;
            animation_ticks_left = animation_usa_police[animation_step].ticks;
        }
    }
    set_led(0, animation_usa_police[animation_step].led1);
    set_led(1, animation_usa_police[animation_step].led2);
    animation_ticks_left--;
}

void system_init()
{
    // SMODE IDLE; SEN disabled;
    _PROTECTED_WRITE(SLPCTRL.CTRLA, 0x00);
    // RUNSTDBY disabled;
    _PROTECTED_WRITE(CLKCTRL.OSC32KCTRLA, 0x00);
    // RUNSTDBY disabled;
    _PROTECTED_WRITE(CLKCTRL.OSC20MCTRLA, 0x00);
    // PDIV 2X; PEN enabled;
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLB, CLKCTRL_PEN_bm);
    // CLKOUT disabled; CLKSEL OSC20M;
    _PROTECTED_WRITE(CLKCTRL.MCLKCTRLA, 0x00);
    // LOCKEN disabled;
    _PROTECTED_WRITE(CLKCTRL.MCLKLOCK, 0x00);
    // SLEEP DIS;
    _PROTECTED_WRITE(BOD.CTRLA, 0x00);
    // VLMCFG BELOW; VLMIE disabled;
    BOD.INTCTRL = 0x00;
    // VLMLVL 5ABOVE;
    BOD.VLMCTRLA = 0x00;
}

ISR(RTC_CNT_vect)
{
    if (RTC.INTFLAGS & RTC_OVF_bm)
    {
        RTC.INTFLAGS &= RTC_OVF_bm; // Clear the overflow interrupt flag
        overflow_count++;           // Increment the overflow count
    }
    if (RTC.INTFLAGS & RTC_CMP_bm)
    {
        RTC.INTFLAGS &= RTC_CMP_bm; // Clear the compare match interrupt flag
        PORTA.OUTCLR = PIN6_bm;     // Pull low the PSU bootstrap pin
    }
}

ISR(RTC_PIT_vect)
{
    if (RTC.PITINTFLAGS & RTC_PI_bm)
    {
        RTC.PITINTFLAGS = RTC_PI_bm; // Clear the PIT interrupt flag
        do_animation_tick(); // Call the animation tick function
    }
}

void pit_rtc_init()
{
    // Datasheet asks to wait for RTC to be ready before configuring it, it seems the RTC does not work properly if we don't wait for it
    while (RTC.STATUS > 0)
        ; // Wait for RTC to be ready
    while (RTC.PITSTATUS > 0)
        ; // Wait for PIT to be ready

    RTC.PER = 0xFFFF; // Set the RTC period to maximum (16-bit)
    RTC.CNT = 0x0000; // Initialize the RTC counter to 0
    RTC.CMP = 30;
    RTC.CLKSEL = RTC_CLKSEL_INT1K_gc;
    RTC.INTCTRL = RTC_OVF_bm; // Low level interrupt
    RTC.INTCTRL = RTC_CMP_bm;   // Compare match interrupt
    RTC.PITINTCTRL = RTC_PI_bm; // Enable PIT interrupt
    RTC.PITCTRLA = RTC_PERIOD_CYC32_gc | RTC_PITEN_bm;
    RTC.CTRLA = RTC_PRESCALER_DIV1024_gc | RTC_RTCEN_bm;
}

void setup_ac()
{
    VREF.CTRLA = VREF_DAC0REFSEL_2V5_gc; // Set the reference voltage to 0.55V
    VREF.CTRLB = VREF_DAC0REFEN_bm; // Enable the reference voltage
    // Set up the AC (Analog Comparator) for the LED
    AC0.CTRLA = AC_ENABLE_bm;
    AC0.MUXCTRLA = (0x02 << AC_MUXPOS_gp) | (0x00 << AC_MUXNEG_gp) | AC_INVERT_bm; // Set the positive and negative inputs for the AC
}

void setup_adc()
{
    // Set up the ADC (Analog-to-Digital Converter) for the LED
    ADC0.CTRLA = ADC_ENABLE_bm | ADC_FREERUN_bm;
    ADC0.CTRLC = (0x01 << ADC_REFSEL_gp);
    ADC0.MUXPOS = 0x07;
}

int main(void)
{
    system_init(); // Initialize the system

    // Initialize the LEDs
    leds_init();
    pit_rtc_init(); // Initialize the RTC and PIT
    //setup_ac(); // Set up the AC (Analog Comparator)
    //setup_adc(); // Set up the    ADC (Analog-to-Digital Converter)
    sei(); // Enable global interrupts

    PORTA.DIRSET = PIN6_bm; // PSU bootstrap
    PORTA.OUTSET = PIN6_bm; // PSU bootstrap

    
    
    
    while (1)
    {
    // if AC0 is triggered, turn on the LED
        // if (AC0.STATUS & AC_STATE_bm)
        // {
        //     set_led(0, COLOR_RED); // Set the LED to red
        //     set_led(1, COLOR_OFF); // Set the LED to off
        // }
        // else
        // {
        //     set_led(0, COLOR_OFF); // Set the LED to off
        //     set_led(1, COLOR_BLUE); // Set the LED to blue
        // }
        //Wait for ADC conversion to complete
        // ADC0.COMMAND = ADC_STCONV_bm; // Start the ADC conversion
        // while (!(ADC0.INTFLAGS & ADC_RESRDY_bm));
        // // Read the ADC result
        // uint16_t adc_result = ADC0.RES; // Read the ADC result
        // // Check if the ADC result is above a certain threshold
        // if (adc_result > 0x10F) // If the ADC result is above the threshold
        // {
        //     // Turn on the LED
        //     set_led(0, COLOR_RED); // Set the LED to red
        //     set_led(1, COLOR_OFF); // Set the LED to off
        // }
        // else
        // {
        //     // Turn off the LED
        //     set_led(0, COLOR_OFF); // Set the LED to off
        //     set_led(1, COLOR_BLUE); // Set the LED to blue
        // }
    }

    return 0;
}