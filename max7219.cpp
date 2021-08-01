#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsometimes-uninitialized"
#include <util/delay.h>
#pragma clang diagnostic pop

#include "max7219.h"

namespace max7219 {

static void writeBit(max7219_t &max, bool bit) {
  if (bit) {
    *max.port |= max.bitDataInput;
  } else {
    *max.port &= ~max.bitDataInput;
  }
  *max.port |= max.bitClock;
  _delay_us(max.clockDelayMicro);
  *max.port &= ~max.bitClock;
  _delay_us(max.clockDelayMicro);
}

static void write(max7219_t &max, uint8_t data) {
  for (int index = 7; index >= 0; --index) {
    writeBit(max, (data >> index) & 0b1);
  }
}

void sendCommand(max7219_t &max, const command_t &command) {
  *max.port &= ~max.bitClock;
  *max.port &= ~max.bitChipSelect;

  switch (command.type) {
  case BRIGHTNESS: {
    write(max, BRIGHTNESS);
    write(max, command.command.brightness.intensity);
    break;
  }
  case DECODE_MODE: {
    write(max, DECODE_MODE);
    write(max, 0);
    break;
  }
  case SCAN_LIMIT: {
    write(max, SCAN_LIMIT);
    write(max, command.command.scanLimit.digits);
    break;
  }
  case SHUTDOWN: {
    write(max, SHUTDOWN);
    write(max, command.command.shutdown.state);
    break;
  }
  case TEST: {
    write(max, TEST);
    write(max, command.command.test.start);
    break;
  }
  }

  *max.port &= ~max.bitClock;
  *max.port |= max.bitChipSelect;
  _delay_us(max.clockDelayMicro);
}

void sendData(max7219_t &max, uint8_t row, uint8_t data) {
  *max.port &= ~max.bitClock;
  *max.port &= ~max.bitChipSelect;

  write(max, row & 0b1111);
  write(max, data);

  *max.port &= ~max.bitClock;
  *max.port |= max.bitChipSelect;
  _delay_us(max.clockDelayMicro);
}

} // namespace max7219
