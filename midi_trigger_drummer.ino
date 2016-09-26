#include "midi.h"
#include "drum_triggers.h"
#include "display.h"
#include "user_inputs.h"

void setup() {
  MIDI::setup();
  DrumTriggers::setup();
  Display::setup();
  Display::displayDec(MIDI::channel + 1, false, false, false);
}

void loop() {
  MIDI::process_messages();
  UserInputs::process_user_inputs();
}
