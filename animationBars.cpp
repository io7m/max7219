#include "animationBars.h"

namespace animation {

static void reload(max7219::max7219_t &max) {
  {
    max7219::command_t cmd;
    cmd.type = max7219::BRIGHTNESS;
    cmd.command.brightness.intensity = 0;
    max7219::sendCommand(max, cmd);
  }
}

static uint8_t BAR = 0;

static void show(max7219::max7219_t &max, uint8_t frame) {
  if (BAR == 8) {
    BAR = 1;
  } else {
    BAR = BAR + 1;
  }

  for (int row = 1; row <= 8; ++row) {
    if (row == BAR) {
      max7219::sendData(max, row, 0b11111111);
    } else {
      max7219::sendData(max, row, 0b00000000);
    }
  }
}

struct animation_t makeBars() {
  return animation_t{&reload, &show

  };
}

}; // namespace animation
