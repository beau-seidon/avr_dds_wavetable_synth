#include "avr_config.h"


void analog_output_setup()
{
    /*  turn on fast PWM and OC0A output at full clock rate, toggle OC0A (pin B3) @ 16 microsec per PWM cycle sample time  */

    /*  timer 0  */
    // DDRB = (1 << PINB3);                                                   // make B.3 an output
    // TCCR0B = 1;                                                            // timer 0 runs at full rate
    // TIMSK0 = 0;                                                            // turn off timer 0 overflow ISR
    // TCCR0A = (1 << COM0A0) | (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);  // set to fast waveform generation mode
    // OCR0A = 128;                                                           // set PWM to half full scale

    /*  timer 3  */
    DDRC = (1 << PINC6);
    TCCR3B = (1 << WGM32) | (1 << CS30);
    TIMSK3 = 0;
    TCCR3A = (1 << COM3A0) | (1 << COM3A1) | (1 << WGM30);
    OCR3A = 128;
}



void phase_accumulator_setup()
{
    /*  timer 1 ticks at 16 kHz or 62.5 microsecs; period = 1000 ticks  */
    OCR1A = (int)((F_CPU / SAMPLE_RATE) - 1);  // 1000 ticks = 16 KHz
    TIMSK1 = (1 << OCIE1A);                    // enable interrupt on compare match A
    TCCR1B = (1 << WGM12) | (1 << CS10);       // full speed; clear-on-match
    TCCR1A = 0x00;                             // turn off pwm and oc lines
    TCNT1 = 0;
}
