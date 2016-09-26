#include "midi.h"
#include "drum_triggers.h"
#include <Arduino.h>

namespace MIDI {
  uint8_t channel = 0;
  uint8_t command_in = 0;
  int8_t key = -1;

  void setup() {
    Serial1.begin(31250);
  }

  void process_messages() {
    while (Serial1.available() > 0) {
      uint8_t midi_data = Serial1.read();

      if (midi_data >= MIDI_NOTE_OFF) {
        uint8_t received_channel = midi_data % 0x10;

        command_in = received_channel == channel ?
            command_in = midi_data - channel :
            0;
      } else if (key == -1) {
        if (command_in == MIDI_NOTE_ON) {
          key = midi_data;
        }
      } else {
        if (command_in == MIDI_NOTE_ON &&
            midi_data > 0x00 &&
            key >= MIDI_FIRST_KEY &&
            key < MIDI_FIRST_KEY + DRUM_TRIGGERS) {
          DrumTriggers::hit(key - MIDI_FIRST_KEY);
        }

        key = -1;
      }
    }
  }
}
