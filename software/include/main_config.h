#pragma once

#include <Arduino.h>
#include "parameters.h"



#define MAX_AMP 32767
#define MAX_VOICES 6

const double SAMPLE_RATE = 44100;  // samples per second

const double Cs133_Hz = 273.961775600910186767578125;
const double COSMIC_INTERVAL = EULER * PI *  M_SQRT2;

/*  tuning correction factor  */
// const double K = 1.0;  // no tuning correction
// const double K = 1000.0 / 1174.0;  // 1 voice, 8000 hz sample rate
// const double K = 1000.0 / 1039.0;  // 1 voice, 16000 hz sample rate
// const double K = 1000.0 / 1198.0;  // 1 voice, 44100 hz sample rate
// const double K = 1000.0 / 646.1;  // 2 voice, 16000 hz sample rate
// const double K = 1000.0 / 463.4 / 1.039;  // 3 voice, 16000 hz sample rate
// const double K = 1000.0 / 481.6;  // 3 voice, 44100 hz sample rate
const double K = 1000.0 / 296.55;  // 6 voice, 441000 hz sample rate
