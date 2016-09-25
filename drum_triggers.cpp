#include "drum_triggers.h"
#include <Arduino.h>

namespace DrumTriggers {
  uint8_t drum_pin_map[DRUM_TRIGGERS] = {10, 14};

  void setup() {
    for (uint8_t drum_i = 0; drum_i < DRUM_TRIGGERS; drum_i++) {
      pinMode(drum_pin_map[drum_i], OUTPUT);
    }
  }

  void hit(uint8_t drum) {
    digitalWrite(drum_pin_map[drum], HIGH);
    digitalWrite(drum_pin_map[drum], LOW);
  }
}
