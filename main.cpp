#include "uart.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsometimes-uninitialized"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#pragma clang diagnostic pop

#include "animationBars.h"
#include "animationFace.h"
#include "animationFade.h"
#include "animationNoise.h"
#include "max7219.h"

static void timerSetup() {

  /*
   * Configure the timer to use a /1024 prescaler.
   *
   * With a /1024 prescaler, it would take (1 / (16000000 / 1024)) seconds = 64
   * useconds to increment the timer once. With an 8-bit timer, the timer would
   * overflow in 64 * 255 = 16320 useconds.
   */

  PRR0 &= ~(1 << PRTIM0);
  PRR0 &= ~(1 << PRTIM2);

  TCCR0B = 0b00000101;
  TCNT0 = 0;
}

static void timerReset() {
  TCNT0 = 0;
  TIFR0 &= ~(1 << TOV0);
}

static bool timerHasCounted16ms() { return TCNT0 >= 250; }

static void run(void) {
  uart_init();
  uart_puts("I: start\n");

  timerSetup();

  DDRA = 0b11111111;
  PORTA = 0b00000000;

  max7219::max7219_t max;
  max.port = &PORTA;
  max.bitClock = 0b00000001;
  max.bitChipSelect = 0b00000010;
  max.bitDataInput = 0b00000100;
  max.timerControl = &TCCR2B;
  max.timerCount = &TCNT2;
  max7219::start(max);

  uart_puts("I: off\n");
  {
    max7219::command_t cmd;
    cmd.type = max7219::SHUTDOWN;
    cmd.command.shutdown.state = max7219::SHUTDOWN_OFF;
    max7219::sendCommand(max, cmd);
  }

  uart_puts("I: no-decode\n");
  {
    max7219::command_t cmd;
    cmd.type = max7219::DECODE_MODE;
    max7219::sendCommand(max, cmd);
  }

  uart_puts("I: brightness\n");
  {
    max7219::command_t cmd;
    cmd.type = max7219::BRIGHTNESS;
    cmd.command.brightness.intensity = 0;
    max7219::sendCommand(max, cmd);
  }

  uart_puts("I: scan-limit\n");
  {
    max7219::command_t cmd;
    cmd.type = max7219::SCAN_LIMIT;
    cmd.command.scanLimit.digits = 0b1111;
    max7219::sendCommand(max, cmd);
  }

  uart_puts("I: on\n");
  {
    max7219::command_t cmd;
    cmd.type = max7219::SHUTDOWN;
    cmd.command.shutdown.state = max7219::SHUTDOWN_ON;
    max7219::sendCommand(max, cmd);
  }

  uint32_t iteration = 0;
  uint8_t animationCurrent = 0;

  const struct animation::animation_t animations[] = {
      animation::makeFace(), animation::makeFade(), animation::makeNoise(),
      animation::makeBars()};
  const uint8_t animationCount = sizeof(animations) / sizeof(animations[0]);

  for (;;) {
    timerReset();

    if (iteration % 120 == 0) {
      animationCurrent = (animationCurrent + 1) % animationCount;
      animations[animationCurrent].reload(max);
    }

    animations[animationCurrent].show(max, iteration);

    for (;;) {
      if (timerHasCounted16ms()) {
        break;
      }
    }

    ++iteration;
  }
}

extern "C" {
int main(void) {
  run();
  return 0;
}
}
