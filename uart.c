#include "uart.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/setbaud.h>

#ifdef __cplusplus
extern "C" {
#endif

void uart_init() {
  UBRR3H = UBRRH_VALUE;
  UBRR3L = UBRRL_VALUE;

#if USE_2X
  UCSR3A |= _BV(U2X3);
#else
  UCSR3A &= ~(_BV(U2X3));
#endif

  UCSR3C = _BV(UCSZ31) | _BV(UCSZ30);
  UCSR3B = _BV(RXEN3) | _BV(TXEN3);
}

int uart_putchar(char c) {
  if (c == '\n') {
    uart_putchar('\r');
  }
  loop_until_bit_is_set(UCSR3A, UDRE3);
  UDR3 = c;
  return 0;
}

int uart_getchar() {
  loop_until_bit_is_set(UCSR3A, RXC3);
  return UDR3;
}

void uart_puts(const char *text) {
  const char *ptr = text;
  for (;;) {
    char c = *ptr;
    if (c == 0) {
      break;
    }
    uart_putchar(c);
    ++ptr;
  }
}

void uart_putu32(uint32_t x) {
  char buffer[12] = {0};
  snprintf(buffer, sizeof(buffer), "%u", x);
  uart_puts(buffer);
}

void uart_putd32(int32_t x) {
  char buffer[13] = {0};
  snprintf(buffer, sizeof(buffer), "%d", x);
  uart_puts(buffer);
}

void uart_putu8b(uint8_t x) {
  char buffer[9] = {0};
  for (int index = 7; index >= 0; --index) {
    uint8_t bit = (x >> index) & 1;
    if (bit) {
      buffer[7 - index] = '1';
    } else {
      buffer[7 - index] = '0';
    }
  }
  uart_puts(buffer);
}

void uart_putu16b(uint16_t x) {
  char buffer[17] = {0};
  for (int index = 15; index >= 0; --index) {
    uint8_t bit = (x >> index) & 1;
    if (bit) {
      buffer[15 - index] = '1';
    } else {
      buffer[15 - index] = '0';
    }
  }
  uart_puts(buffer);
}

void uart_putu32x(uint32_t x) {
  char buffer[12] = {0};
  snprintf(buffer, sizeof(buffer), "%x", x);
  uart_puts(buffer);
}

void uart_putf32(float x) {
  char buffer[64] = {0};
  snprintf(buffer, sizeof(buffer), "%f", x);
  uart_puts(buffer);
}

#ifdef __cplusplus
}
#endif
