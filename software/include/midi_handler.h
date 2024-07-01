#pragma once

#include <Arduino.h>
#include "parameters.h"
#include <USB-MIDI.h>



void midi_setup(byte channel);
void midi_read(void);
void handleNoteOn(byte channel, byte note, byte vel);
void handleNoteOff(byte channel, byte note, byte vel);
