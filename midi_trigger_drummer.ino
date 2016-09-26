#include "midi.h"
#include "drum_triggers.h"
#include "display.h"
#include "user_inputs.h"

void setup() {
  MIDI::setup();
  DrumTriggers::setup();
  Display::setup();
  Display::display_midi_channel(false);
}

void loop() {
  MIDI::process_messages();
  UserInputs::process_user_inputs();
}
