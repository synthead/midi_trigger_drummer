#include "user_inputs.h"
#include "midi.h"
#include "display.h"
#include <Arduino.h>

namespace UserInputs {
  bool button_up_state = false;
  bool last_button_up_state = false;
  bool button_up_event = false;

  bool button_down_state = false;
  bool last_button_down_state = false;
  bool button_down_event = false;

  uint8_t menu = MENU_NONE;
  unsigned long menu_expires_at = 0;

  void setup() {
    pinMode(BUTTON_UP_PIN, INPUT);
    pinMode(BUTTON_DOWN_PIN, INPUT);
  }

  void set_menu_timeout() {
    menu_expires_at = millis() + MENU_TIMEOUT;
  }

  void process_user_inputs() {
    bool button_up_state = digitalRead(BUTTON_UP_PIN);
    bool button_down_state = digitalRead(BUTTON_DOWN_PIN);

    if (! last_button_up_state && button_up_state) {
      last_button_up_state = true;
      button_up_event = true;
    } else if (last_button_up_state && ! button_up_state) {
      last_button_up_state = false;
      set_menu_timeout();
    }

    if (! last_button_down_state && button_down_state) {
      last_button_down_state = true;
      button_down_event = true;
    } else if (last_button_down_state && ! button_down_state) {
      last_button_down_state = false;
      set_menu_timeout();
    }

    if (button_up_event || button_down_event) {
      switch (menu) {
        case MENU_NONE:
          if (button_up_event) {
            menu = MENU_MIDI_CHANNEL;
            Display::display_midi_channel(MIDI_CHANNEL_EDIT_ON);
          } else if (button_down_event) {
            // menu = MENU_FIRST_KEY;
          }
          break;

        case MENU_MIDI_CHANNEL:
          MIDI::shift_channel(button_up_event);
          Display::display_midi_channel(MIDI_CHANNEL_EDIT_ON);
          break;

        // case MENU_FIRST_KEY:
        //   break;
      }

      button_up_event = button_down_event = false;
    }

    if (menu != MENU_NONE &&
        ! button_up_state &&
        ! button_down_state &&
        millis() >= menu_expires_at) {
      menu = MENU_NONE;
      Display::display_midi_channel(MIDI_CHANNEL_EDIT_OFF);
    }
  }
}

