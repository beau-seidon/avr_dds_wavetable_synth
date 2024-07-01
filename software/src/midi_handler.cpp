#include "midi_handler.h"



volatile byte note_buffer[MAX_VOICES] = { 255, 255, 255, 255, 255, 255 };
volatile byte active_notes = 0;  // Gate will be open while any keys are pressed (any notes active)



USBMIDI_CREATE_DEFAULT_INSTANCE();



void midi_setup(byte channel = MIDI_CHANNEL_OMNI)
{
    MIDI.begin(channel);
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
}



void midi_read()
{
    MIDI.read();
    // Serial.begin(9600);
}



void handleNoteOn(byte channel, byte note, byte vel)
{
    if (active_notes < MAX_VOICES) {  // If note is already in the buffer, do nothing
        for (byte n = 0; n < active_notes; n++) {
            if (note_buffer[n] == note) {
                return;
            }
        }

        note_buffer[active_notes] = note;
        active_notes++;

        if (active_notes) phase_increment[active_notes-1] = pitch[note_buffer[active_notes-1]];

        // // debug:
        // Serial.print("note on: "); Serial.print(note); Serial.print("; active notes = "); Serial.println(active_notes);
        // Serial.print("buffer: [");
        // for (int i = 0; i < MAX_VOICES; i++) {
        //     Serial.print(note_buffer[i]); Serial.print(",");
        // }
        // Serial.println("]");
    }
}



void handleNoteOff(byte channel, byte note, byte vel)
{
    bool note_off_match = false;

    for (uint8_t n = 0; n < active_notes; n++) {  // Check buffer to see if note is active
        if (note_buffer[n] == note) {
            note_off_match = true;
            if (n < (active_notes-1)) {  // If note is removed from buffer, shift remaining notes down to prevent empty slots
                note_buffer[n] = note_buffer[n+1];
                note_buffer[n+1] = note;
            }
        }
    }

    if (note_off_match) {
        note_off_match = false;
        active_notes--;

        note_buffer[active_notes] = 255;  // Remove requested note and play next note in buffer

        for (int v = 0; v < MAX_VOICES; v++){
            if (note_buffer[v] == 255)
                phase_increment[v] = 0;
            else
                phase_increment[v] = pitch[note_buffer[v]];
        }

        // // debug:
        // Serial.print("note off: "); Serial.print(note); Serial.print("; active notes = "); Serial.println(active_notes);
        // Serial.print("buffer: [");
        // for (int i = 0; i < MAX_VOICES; i++) {
        //     Serial.print(note_buffer[i]); Serial.print(",");
        // }
        // Serial.println("]");
    }
}
