#ifndef UART_H
#define UART_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void uart_init();
int uart_putchar(char);
int uart_getchar();
void uart_puts(const char *text);
void uart_putu32(uint32_t x);
void uart_putd32(int32_t x);
void uart_putu32x(uint32_t x);
void uart_putu8b(uint8_t x);
void uart_putu16b(uint16_t x);

#ifdef __cplusplus
}
#endif

#endif // UART_H
