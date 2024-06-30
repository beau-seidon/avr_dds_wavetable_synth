#include <Arduino.h>
#include "parameters.h"
#include "avr_config.h"
#include "midi_handler.h"
#include "voice_config.h"



ISR (TIMER1_COMPA_vect)
{
    /*  compute exponential attack and decay of amplitude; the (time & 0x0ff) slows down the decay computation by 256 times  */
    if ((time & 0xff) == 0) {
        for (int v = 0; v < MAX_VOICES; v++) {
            decay[v] = decay[v] - (decay[v] >> decay_const[v]);
            attack[v] = attack[v] - (attack[v] >> attack_const[v]);
        }
    }

    /*  reinitialize the amplitude envelope  */
    if (trigger == 1) {
        for (int v = 0; v < MAX_VOICES; v++) {
            decay[v] = MAX_AMP;
            attack[v] = MAX_AMP;
        }
        trigger = 0;
    }

    char normalized_amplitude = 0;
    for (int v = 0; v < MAX_VOICES; v++) {
        /*  form (1 - exp(-t / tau)) for the attack phase; product of rise and fall exponentials is the amplitude envelope  */

        amplitude[v] = MAX_AMP / MAX_VOICES;  // ((MAX_AMP - attack[v]) >> 8) * (decay[v] >> 8);

        phase_accumulator[v] = phase_accumulator[v] + phase_increment[v];
        phase_acc_msb[v] = (char)(phase_accumulator[v] >> 8);

        sine[v] = (char)((((amplitude[v] >> 8) * (int)wavetable[phase_acc_msb[v]])) >> a[v]);

        normalized_amplitude += sine[v];
    }

    /*  output the wavefrom sample, scale amplitude to use only high byte and shift into range 0 to 255  */
    OCR3A = 128 + normalized_amplitude;

    time++;  // ticks at 16 KHz
}



void setup()
{
    time = 0;

    pitch_table_setup();
    wavetable_setup();
    voice_setup();
    analog_output_setup();
    phase_accumulator_setup();
    midi_setup(MIDI_CHANNEL_OMNI);

    sei();  // turn on all ISRs
}



void loop()
{
    midi_read();
    // /*  retrigger note after a 1 second time delay  */
    // if (time >= SAMPLE_RATE / 8) {
    //     // note += 4;
    //     // note = (note >= 127) ? 0 : note;
    //     // phase_increment[0] = pitch[note] / k;
    //     trigger = 1;
    //     time = 0;
    // }
}
