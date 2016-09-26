#ifndef CHANNEL_DISPLAY_H
#define CHANNEL_DISPLAY_H

#include <stdint.h>

#define DISPLAY_DATA 2
#define DISPLAY_CLK 3
#define DISPLAY_LATCH 4

namespace Display {
  void setup();
  void display(uint8_t, uint8_t, bool, bool, bool);
  void display_hex(uint8_t, bool, bool, bool);
  void display_decimal(uint8_t, bool, bool, bool);
  void display_midi_channel(bool);
  void display_midi_first_key(bool);
}

#endif
