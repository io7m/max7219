
#include "animationNoise.h"

namespace animation {

static const uint8_t NOISE[] = {0xbd, 0xf2, 0x66, 0xac, 0x21, 0x9d, 0x29, 0xac,
                                0xf8, 0x45, 0xf5, 0xa0, 0x5e, 0x12, 0xb5, 0x2a,
                                0x12, 0xec, 0x05, 0xd7, 0x5d, 0xa5, 0x9e, 0xed,
                                0x60, 0x4d, 0xa8, 0x85, 0x51, 0x6c, 0x4f, 0x49};

static uint8_t NOISE_INDEX = 0;

static void reload(max7219::max7219_t &max) {
  {
    max7219::command_t cmd;
    cmd.type = max7219::BRIGHTNESS;
    cmd.command.brightness.intensity = 0;
    max7219::sendCommand(max, cmd);
  }
}

static void show(max7219::max7219_t &max, uint8_t frame) {
  for (int row = 1; row <= 8; ++row) {
    const uint8_t noise = NOISE[NOISE_INDEX];
    NOISE_INDEX = (NOISE_INDEX + 1) % sizeof(NOISE);
    max7219::sendData(max, row, noise ^ frame);
  }
}

struct animation_t makeNoise() {
  return animation_t{&reload, &show

  };
}

}; // namespace animation
