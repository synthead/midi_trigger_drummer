#ifndef USER_INPUTS_H
#define USER_INPUTS_H

#define BUTTON_UP_PIN 6
#define BUTTON_DOWN_PIN 7

#define MENU_NONE 0
#define MENU_MIDI_CHANNEL 1
#define MENU_FIRST_KEY 2

#define MENU_TIMEOUT 5000

namespace UserInputs {
  void setup();
  void set_menu_timeout();
  void process_user_inputs();
}

#endif
