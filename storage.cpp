#include "midi.h"
#include "storage.h"
#include <EEPROM.h>

namespace Storage {
  void read_settings() {
    if (EEPROM.read(EEPROM_VALIDATION_LOCATION) == EEPROM_VALIDATION_VALUE) {
      MIDI::settings.channel = EEPROM.read(EEPROM_MIDI_CHANNEL_LOCATION);
      MIDI::settings.first_key = EEPROM.read(EEPROM_MIDI_FIRST_KEY_LOCATION);
    } else {
      MIDI::settings.channel = MIDI_CHANNEL_DEFAULT;
      MIDI::settings.first_key = MIDI_FIRST_KEY_DEFAULT;

      EEPROM.write(EEPROM_VALIDATION_LOCATION, EEPROM_VALIDATION_VALUE);
      write_settings();
    }
  }

  void write_settings() {
    EEPROM.write(EEPROM_MIDI_CHANNEL_LOCATION, MIDI::settings.channel);
    EEPROM.write(EEPROM_MIDI_FIRST_KEY_LOCATION, MIDI::settings.first_key);
  }
}
