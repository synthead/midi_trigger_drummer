#include "user_inputs.h"
#include "midi.h"
#include "display.h"
#include <Arduino.h>

namespace UserInputs {
  bool button_up_state;
  bool last_button_up_state = false;
  bool button_up_event = false;

  bool button_down_state;
  bool last_button_down_state = false;
  bool button_down_event = false;

  uint8_t menu = MENU_NONE;
  unsigned long menu_expires_at;

  uint8_t menu_strobe_state;
  unsigned long menu_strobe_expires_at;

  void setup() {
    pinMode(BUTTON_UP_PIN, INPUT);
    pinMode(BUTTON_DOWN_PIN, INPUT);
  }

  void set_menu_timeout() {
    unsigned long now = millis();
    menu_expires_at = now + MENU_TIMEOUT;

    if (menu == MENU_NONE) {
      menu_strobe_expires_at = now + MENU_STROBE_TIMEOUT;
      menu_strobe_state = true;
    }
  }

  void process_user_inputs() {
    bool button_up_state = digitalRead(BUTTON_UP_PIN);
    bool button_down_state = digitalRead(BUTTON_DOWN_PIN);

    if (! last_button_up_state && button_up_state) {
      last_button_up_state = true;
      button_up_event = true;
    } else if (last_button_up_state && ! button_up_state) {
      last_button_up_state = false;
    }

    if (! last_button_down_state && button_down_state) {
      last_button_down_state = true;
      button_down_event = true;
    } else if (last_button_down_state && ! button_down_state) {
      last_button_down_state = false;
    }

    if (button_up_state || button_down_state) {
      set_menu_timeout();
    }

    if (button_up_event || button_down_event) {
      switch (menu) {
        case MENU_NONE:
          if (button_up_event) {
            menu = MENU_MIDI_CHANNEL;
            Display::display_midi_channel(menu_strobe_state);
          } else if (button_down_event) {
            // menu = MENU_FIRST_KEY;
          }
          break;

        case MENU_MIDI_CHANNEL:
          MIDI::shift_channel(button_up_event);
          Display::display_midi_channel(menu_strobe_state);
          break;

        // case MENU_FIRST_KEY:
        //   break;
      }

      button_up_event = button_down_event = false;
    }

    if (menu != MENU_NONE) {
      unsigned long now = millis();

      if (now >= menu_expires_at) {
        menu = MENU_NONE;
        Display::display_midi_channel(false);
      } else if (now >= menu_strobe_expires_at) {
        menu_strobe_state = ! menu_strobe_state;
        menu_strobe_expires_at += MENU_STROBE_TIMEOUT;

        switch (menu) {
          case MENU_MIDI_CHANNEL:
            Display::display_midi_channel(menu_strobe_state);
            break;

          // case MENU_FIRST_KEY:
          //   break;
        }
      }
    }
  }
}

