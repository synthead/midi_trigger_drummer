#include "user_inputs.h"
#include "midi.h"
#include "display.h"
#include "storage.h"
#include <Arduino.h>

namespace UserInputs {
  bool button_right_state;
  bool last_button_right_state = false;
  bool button_right_event = false;

  bool button_left_state;
  bool last_button_left_state = false;
  bool button_left_event = false;

  unsigned long now;

  uint8_t menu = MENU_NONE;
  unsigned long menu_expires_at;

  uint8_t menu_strobe_state;
  unsigned long menu_strobe_expires_at;

  unsigned long button_repeat_expires_at;

  MIDI::settings_struct last_midi_settings;

  void setup() {
    pinMode(BUTTON_LEFT_PIN, INPUT);
    pinMode(BUTTON_RIGHT_PIN, INPUT);
  }

  void set_menu_timeout() {
    now = millis();
    menu_expires_at = now + MENU_TIMEOUT;

    if (menu == MENU_NONE) {
      menu_strobe_expires_at = now + MENU_STROBE_TIMEOUT;
      menu_strobe_state = true;
    }
  }

  void set_button_repeat_timeout() {
    button_repeat_expires_at = millis() + MENU_BUTTON_REPEAT_TIMEOUT;
  }

  void process_user_inputs() {
    button_left_state = digitalRead(BUTTON_LEFT_PIN);
    button_right_state = digitalRead(BUTTON_RIGHT_PIN);

    if (! last_button_right_state && button_right_state) {
      last_button_right_state = true;
      button_right_event = true;
      set_button_repeat_timeout();
    } else if (last_button_right_state && ! button_right_state) {
      last_button_right_state = false;
    }

    if (! last_button_left_state && button_left_state) {
      last_button_left_state = true;
      button_left_event = true;
      set_button_repeat_timeout();
    } else if (last_button_left_state && ! button_left_state) {
      last_button_left_state = false;
    }

    if (button_right_state || button_left_state) {
      set_menu_timeout();
    }

    if (millis() >= button_repeat_expires_at) {
      button_repeat_expires_at += MENU_BUTTON_REPEAT_RATE;

      button_left_event = button_left_state;
      button_right_event = button_right_state;
    }

    if (button_right_event || button_left_event) {
      switch (menu) {
        case MENU_NONE:
          last_midi_settings = MIDI::settings;

          if (button_left_event) {
            menu = MENU_MIDI_CHANNEL;
            Display::display_midi_channel(menu_strobe_state);
          } else if (button_right_event) {
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
      now = millis();

      if (now >= menu_expires_at) {
        switch (menu) {
          case MENU_MIDI_CHANNEL:
            if (MIDI::settings.channel != last_midi_settings.channel) {
              Storage::write_midi_channel();
            }
            break;

          case MENU_MIDI_FIRST_KEY:
            if (MIDI::settings.first_key != last_midi_settings.first_key) {
              Storage::write_midi_first_key();
            }
            break;
        }

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

