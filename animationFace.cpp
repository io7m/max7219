#include "animationFace.h"

namespace animation {

static void reload(max7219::max7219_t &max) {
  max7219::sendData(max, 1, 0b11111111);
  max7219::sendData(max, 2, 0b10000001);
  max7219::sendData(max, 3, 0b10111101);
  max7219::sendData(max, 4, 0b10100101);
  max7219::sendData(max, 5, 0b10100101);
  max7219::sendData(max, 6, 0b10111101);
  max7219::sendData(max, 7, 0b10000001);
  max7219::sendData(max, 8, 0b11111111);
}

static void show(max7219::max7219_t &max, uint8_t frame) {
  {
    max7219::command_t cmd;
    cmd.type = max7219::BRIGHTNESS;
    cmd.command.brightness.intensity = frame & 0b111;
    max7219::sendCommand(max, cmd);
  }
}

struct animation_t makeFace() {
  return animation_t{&reload, &show

  };
}

}; // namespace animation
