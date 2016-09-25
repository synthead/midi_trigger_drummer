#include "midi.h"
#include "drum_triggers.h"
#include "display.h"

void setup() {
  MIDI::setup();
  DrumTriggers::setup();
  Display::setup();
}

void loop() {
  MIDI::process_messages();
}
