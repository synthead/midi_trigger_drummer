#include "midi.h"
#include "drum_triggers.h"

void setup() {
  MIDI::setup();
  DrumTriggers::setup();
}

void loop() {
  MIDI::process_messages();
}
