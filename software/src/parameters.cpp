#include "parameters.h"



/*  the DDS variables  */
volatile unsigned int phase_accumulator[MAX_VOICES];
volatile unsigned int phase_increment[MAX_VOICES];
volatile unsigned char phase_acc_msb[MAX_VOICES];


/*  tables for DDS and the output waves to be added together  */
char wavetable[256];
char sine[MAX_VOICES];


/*  envelope variables  */
volatile unsigned char attack_const[MAX_VOICES];  // attack time constant
volatile unsigned char decay_const[MAX_VOICES];   // decay time constant
volatile int attack[MAX_VOICES];                  // attack envelope
volatile int decay[MAX_VOICES];                   // decay envelope
volatile int amplitude[MAX_VOICES];               // amplitude waveforms = attack * decay waveforms
volatile unsigned char a[MAX_VOICES];             // amplitude scaling constant

volatile unsigned int trigger;                    // used to reset envelope
volatile unsigned long time;                      // mSec, used to slow down the envelope


/*  midi note to pitch map  */
double pitch[127];
int note = 0;
