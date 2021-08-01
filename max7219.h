#ifndef MAX7219_H
#define MAX7219_H

#include <stdint.h>

namespace max7219 {

typedef struct {
  volatile uint8_t *port;
  uint8_t bitClock;
  uint8_t bitChipSelect;
  uint8_t bitDataInput;
  uint32_t clockDelayMicro;
} max7219_t;

typedef enum {
  TEST = 0b00001111,
  BRIGHTNESS = 0b00001010,
  SCAN_LIMIT = 0b00001011,
  DECODE_MODE = 0b00001001,
  SHUTDOWN = 0b00001100,
} command_type_t;

typedef struct {
  bool start;
} command_test_t;

typedef struct {
  uint8_t intensity;
} command_brightness_t;

typedef enum {
  SHUTDOWN_OFF = 0b00000000,
  SHUTDOWN_ON = 0b00000001
} command_shutdown_state_t;

typedef struct {
  command_shutdown_state_t state;
} command_shutdown_t;

typedef struct {
  uint8_t digits;
} command_scan_limit_t;

struct command_t {
  command_type_t type;
  union {
    command_test_t test;
    command_brightness_t brightness;
    command_shutdown_t shutdown;
    command_scan_limit_t scanLimit;
  } command;
};

void sendCommand(max7219_t &max, const command_t &command);
void sendData(max7219_t &max, uint8_t row, uint8_t data);

}; // namespace max7219

#endif // MAX7219_H
