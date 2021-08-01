#ifndef ANIMATION_H
#define ANIMATION_H

#include "max7219.h"

namespace animation {

struct animation_t {
  void (*reload)(max7219::max7219_t &max);
  void (*show)(max7219::max7219_t &max, uint8_t frame);
};

}; // namespace animation

#endif // ANIMATION_H
