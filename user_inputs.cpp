#include "user_inputs.h"
#include "midi.h"
#include "display.h"
#include <Arduino.h>

namespace UserInputs {
  bool button_right_state;
  bool last_button_right_state = false;
  bool button_right_event = false;

  bool button_left_state;
  bool last_button_left_state = false;
  bool button_left_event = false;

  uint8_t menu = MENU_NONE;
  unsigned long menu_expires_at;

  uint8_t menu_strobe_state;
  unsigned long menu_strobe_expires_at;

  void setup() {
    pinMode(BUTTON_LEFT_PIN, INPUT);
    pinMode(BUTTON_RIGHT_PIN, INPUT);
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
    bool button_right_state = digitalRead(BUTTON_LEFT_PIN);
    bool button_left_state = digitalRead(BUTTON_RIGHT_PIN);

    if (! last_button_right_state && button_right_state) {
      last_button_right_state = true;
      button_right_event = true;
    } else if (last_button_right_state && ! button_right_state) {
      last_button_right_state = false;
    }

    if (! last_button_left_state && button_left_state) {
      last_button_left_state = true;
      button_left_event = true;
    } else if (last_button_left_state && ! button_left_state) {
      last_button_left_state = false;
    }

    if (button_right_state || button_left_state) {
      set_menu_timeout();
    }

    if (button_right_event || button_left_event) {
      switch (menu) {
        case MENU_NONE:
          if (button_right_event) {
            menu = MENU_MIDI_CHANNEL;
            Display::display_midi_channel(menu_strobe_state);
          } else if (button_left_event) {
            menu = MENU_MIDI_FIRST_KEY;
            Display::display_midi_first_key(menu_strobe_state);
          }
          break;

        case MENU_MIDI_CHANNEL:
          MIDI::shift_channel(button_right_event);
          Display::display_midi_channel(menu_strobe_state);
          break;

        case MENU_MIDI_FIRST_KEY:
          MIDI::shift_first_key(button_right_event);
          Display::display_midi_first_key(menu_strobe_state);
          break;
      }

      button_right_event = button_left_event = false;
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

          case MENU_MIDI_FIRST_KEY:
            Display::display_midi_first_key(menu_strobe_state);
            break;
        }
      }
    }
  }
}

