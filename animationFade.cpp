
#include "animationFade.h"

namespace animation {

static void reload(max7219::max7219_t &max) {
  max7219::sendData(max, 1, 0b11111111);
  max7219::sendData(max, 2, 0b11111111);
  max7219::sendData(max, 3, 0b11111111);
  max7219::sendData(max, 4, 0b11111111);
  max7219::sendData(max, 5, 0b11111111);
  max7219::sendData(max, 6, 0b11111111);
  max7219::sendData(max, 7, 0b11111111);
  max7219::sendData(max, 8, 0b11111111);
}

static uint8_t delta = 1;
static uint8_t bright = 0;

static void show(max7219::max7219_t &max, uint8_t frame) {
  if (frame % 3 == 0) {
    if (bright >= 7) {
      delta = -1;
    }
    if (bright == 0) {
      delta = 1;
    }
    bright += delta;
  }

  {
    max7219::command_t cmd;
    cmd.type = max7219::BRIGHTNESS;
    cmd.command.brightness.intensity = bright;
    max7219::sendCommand(max, cmd);
  }
}

struct animation_t makeFade() {
  return animation_t{&reload, &show};
}

}; // namespace animation
