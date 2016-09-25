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
  extern uint8_t channel;

  void setup();
  void process_messages();
}

#endif
