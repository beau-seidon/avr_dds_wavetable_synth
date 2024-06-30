#pragma once

#include <Arduino.h>
#include "config.h"


/*  the DDS variables  */
extern volatile unsigned int phase_accumulator[MAX_VOICES];
extern volatile unsigned int phase_increment[MAX_VOICES];
extern volatile unsigned char phase_acc_msb[MAX_VOICES];


/*  tables for DDS and the output waves to be added together  */
extern char wavetable[256];
extern char sine[MAX_VOICES];


/*  envelope variables  */
extern volatile unsigned char attack_const[MAX_VOICES];  // attack time constant
extern volatile unsigned char decay_const[MAX_VOICES];   // decay time constant
extern volatile int attack[MAX_VOICES];                  // attack envelope
extern volatile int decay[MAX_VOICES];                   // decay envelope
extern volatile int amplitude[MAX_VOICES];               // amplitude waveforms = attack * decay waveforms
extern volatile unsigned char a[MAX_VOICES];             // amplitude scaling constant

extern volatile unsigned int trigger;                    // used to reset envelope
extern volatile unsigned long time;                      // mSec, used to slow down the envelope


/*  midi note to pitch map  */
extern double pitch[127];
extern int note;
