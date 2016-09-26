#ifndef CHANNEL_DISPLAY_H
#define CHANNEL_DISPLAY_H

#include <stdint.h>

#define DISPLAY_DATA 2
#define DISPLAY_CLK 3
#define DISPLAY_LATCH1 4
#define DISPLAY_LATCH2 5

namespace Display {
  void setup();
  void display(uint8_t, uint8_t, bool, bool, bool);
  void displayHex(uint8_t, bool, bool, bool);
  void displayDec(uint8_t, bool, bool, bool);
  void displayMidiChannel(bool);
}

#endif
