#ifndef USER_INPUTS_H
#define USER_INPUTS_H

#define BUTTON_LEFT_PIN 6
#define BUTTON_RIGHT_PIN 7

#define MENU_NONE 0
#define MENU_MIDI_CHANNEL 1
#define MENU_MIDI_FIRST_KEY 2

#define MENU_TIMEOUT 3000
#define MENU_STROBE_TIMEOUT 200
#define MENU_BUTTON_REPEAT_TIMEOUT 500
#define MENU_BUTTON_REPEAT_RATE 100

namespace UserInputs {
  void setup();
  void set_menu_timeout();
  void process_user_inputs();
}

#endif
