#include "midi.h"
#include "drum_triggers.h"
#include <Arduino.h>

namespace MIDI {
  settings_struct settings {MIDI_CHANNEL_DEFAULT, MIDI_FIRST_KEY_DEFAULT};
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

        command_in = received_channel == settings.channel ?
            command_in = midi_data - settings.channel :
            0;
      } else if (key == -1) {
        if (command_in == MIDI_NOTE_ON) {
          key = midi_data;
        }
      } else {
        if (command_in == MIDI_NOTE_ON &&
            midi_data > 0x00 &&
            key >= settings.first_key &&
            key < settings.first_key + DRUM_TRIGGERS) {
          DrumTriggers::hit(key - settings.first_key);
        }

        key = -1;
      }
    }
  }

  void shift_channel(bool up) {
    if (up) {
      settings.channel = settings.channel == MIDI_CHANNEL_MAX ?
          0 :
          settings.channel + 1;
    } else {
      settings.channel = settings.channel == 0 ?
          MIDI_CHANNEL_MAX :
          settings.channel - 1;
    }
  }

  void shift_first_key(bool up) {
    if (up) {
      settings.first_key = settings.first_key == MIDI_FIRST_KEY_MAX ?
          0 :
          settings.first_key + 1;
    } else {
      settings.first_key = settings.first_key == 0 ?
          MIDI_FIRST_KEY_MAX :
          settings.first_key - 1;
    }
  }
}
