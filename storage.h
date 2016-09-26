#ifndef STORAGE_H
#define STORAGE_H

#define EEPROM_VALIDATION_LOCATION 0
#define EEPROM_MIDI_CHANNEL_LOCATION 1
#define EEPROM_MIDI_FIRST_KEY_LOCATION 2

#define EEPROM_VALIDATION_VALUE 0b10101010

namespace Storage {
  void read_settings();
  void write_midi_channel();
  void write_midi_first_key();
}

#endif
