#include "midi.h"
#include "drum_triggers.h"
#include "channel_display.h"

void setup() {
  MIDI::setup();
  DrumTriggers::setup();
  ChannelDisplay::setup();
}

void loop() {
  MIDI::process_messages();
}
