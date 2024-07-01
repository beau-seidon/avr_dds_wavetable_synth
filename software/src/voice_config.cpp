#include "voice_config.h"



void pitch_table_setup()
{
    for (int i = 0; i < 127; i++) {
        // pitch[i] = K * (440.0 * pow(2.0, (((double)i - 69.0) / 12.0)));  // A4 = 440 Hz standard tuning and intonation
        pitch[i] = K * (Cs133_Hz * pow(2.0, (((double)i - 61.0) / COSMIC_INTERVAL)));  // C#4 = 25 8va below Cs133 hyperfine transition frequency, wacky intonation
    }
}



void wavetable_setup()
{
    for (int i = 0; i < 256; i++) {
        // wavetable[i] = 127.0 * sin((2.0 * PI) * (double)i / 256.0);  // sine
        wavetable[i] = 127.0 * (double)i / 256.0;  // sawtooth
        // wavetable[i] = (i > 128) ? (255.0 - (127.0 * 2.0 * (double)i) / 256.0) : (127.0 * 2.0 * (double)i / 256.0);  // triangle
    }
}



void voice_setup()
{
    // const double C4 = 261.63;
    // const double E4 = 329.63;
    // const double G4 = 392.00;
    const double TEST_TONE = 0.0;  // 1000.0 * K;

    // const unsigned long ACCUMULATOR_LENGTH = 65536 / (2 * PI);
    // const double PHASE_DURATION = (double)(ACCUMULATOR_LENGTH / 256.0) / SAMPLE_RATE;

    /*  Sound parameters  */
    phase_increment[0] = TEST_TONE;  // frequency. ((2 ^ 16) / 16000) * freq = 4.096 * freq
    decay_const[0] = 0;              // rise and decay SHIFT factors. bigger is slower, max value is 8
    attack_const[0] = 0;
    a[0] = 7;                        // amplitude SHIFT factor. bigger is lower amp, min value is 7

    phase_increment[1] = TEST_TONE;
    decay_const[1] = 0;
    attack_const[1] = 0;
    a[1] = 7;

    phase_increment[2] = TEST_TONE;
    decay_const[2] = 0;
    attack_const[2] = 0;
    a[2] = 7;

    phase_increment[3] = TEST_TONE;
    decay_const[3] = 0;
    attack_const[3] = 0;
    a[3] = 7;

    phase_increment[4] = TEST_TONE;
    decay_const[4] = 0;
    attack_const[4] = 0;
    a[4] = 7;

    phase_increment[5] = TEST_TONE;
    decay_const[5] = 0;
    attack_const[5] = 0;
    a[5] = 7;

    // start with the amp envelope at max
    trigger = 1;
}



/*
Examples:

// Bell
    inc_1 = (int)(8.192 * 262);  // frequency. ((2 ^ 16) / 8000) * freq = 8.192 * freq
    fall_1 = 5;                  // rise and decay SHIFT factors. bigger is slower, max value is 8
    rise_1 = 1;
    a_1 = 8;                     // amplitude SHIFT factor. bigger is lower amp, min value is 7

    inc_2 = (int)(8.192 * 262 * 1.58);
    fall_2 = 5;
    rise_2 = 1;
    a_2 = 7;

    inc_3 = (int)(8.192 * 262 * 2.24);
    fall_3 = 4;
    rise_3 = 1;
    a_3 = 9;

*/
