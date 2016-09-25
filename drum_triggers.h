#ifndef DRUM_TRIGGERS_H
#define DRUM_TRIGGERS_H

#include <stdint.h>

#define DRUM_TRIGGERS 10

namespace DrumTriggers {
  void setup();
  void hit(uint8_t);
}

#endif
