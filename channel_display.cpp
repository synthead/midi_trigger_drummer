#include "channel_display.h"
#include <Arduino.h>

namespace ChannelDisplay {
  uint8_t characters[16] = {
      0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010,
      0b10000010, 0b11111000, 0b10000000, 0b10010000, 0b10100000, 0b10000011,
      0b10100111, 0b10100001, 0b10000100, 0b10001110};

  void setup() {
    pinMode(DISPLAY_DATA, OUTPUT);
    pinMode(DISPLAY_CLK, OUTPUT);
    pinMode(DISPLAY_LATCH1, OUTPUT);
    pinMode(DISPLAY_LATCH2, OUTPUT);
  }

  void display(
      uint8_t digit1_text, uint8_t digit2_text, bool digit1_decimal,
      bool digit2_decimal) {
    digitalWrite(DISPLAY_LATCH1, LOW);
    shiftOut(
        DISPLAY_DATA, DISPLAY_CLK, MSBFIRST,
        characters[digit1_text] - 0b10000000 * digit1_decimal);
    digitalWrite(DISPLAY_LATCH1, HIGH);

    digitalWrite(DISPLAY_LATCH2, LOW);
    shiftOut(
        DISPLAY_DATA, DISPLAY_CLK, MSBFIRST,
        characters[digit2_text] - 0b10000000 * digit2_decimal);
    digitalWrite(DISPLAY_LATCH2, HIGH);
  }

  void displayHex(uint8_t text, bool digit1_decimal, bool digit2_decimal) {
    display(
        (text & 0xf0) >> 4,
        text & 0x0f,
        digit1_decimal,
        digit2_decimal);
  }

  void displayDec(uint8_t text, bool digit1_decimal, bool digit2_decimal) {
    display(
        text / 10,
        text % 10,
        digit1_decimal,
        digit2_decimal);
  }
}
