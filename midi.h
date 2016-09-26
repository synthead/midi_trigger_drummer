#ifndef MIDI_H
#define MIDI_H

#include <stdint.h>

#define MIDI_DEFAULT_CHANNEL 0
#define MIDI_CHANNEL_MAX 15

#define MIDI_NOTE_OFF 0x80
#define MIDI_NOTE_ON 0x90

#define MIDI_KEYS 10
#define MIDI_FIRST_KEY 60

namespace MIDI {
  struct settings_struct {
    uint8_t channel;
    uint8_t first_key;
  };

  extern settings_struct settings;

  void setup();
  void process_messages();
  void shift_channel(bool);
  void shift_first_key(bool);
}

#endif
