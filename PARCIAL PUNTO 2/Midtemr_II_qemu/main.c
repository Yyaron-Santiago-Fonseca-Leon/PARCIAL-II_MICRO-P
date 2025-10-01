#include <stdint.h>
#include "soc_emu_gpio.h"

#define UART0 0x10000000L
#define UART0_LSR (UART0 + 5)

char wr_buffer[256] = "";

// Enviar un carácter
void uart_putc(char c) {
    volatile char *uart = (char *)UART0;
    *uart = c;
}

// Enviar string
void uart_puts(const char *s) {
    while (*s) {
        if (*s == '\n') uart_putc('\r');
        uart_putc(*s++);
    }
}

// Revisar si hay dato disponible
int uart_tstc(void) {
    volatile uint8_t *lsr = (uint8_t *)UART0_LSR;
    return (*lsr & 0x01);
}

// Leer un carácter
char uart_getc(void) {
    volatile char *uart = (char *)UART0;
    while (!uart_tstc());
    return *uart;
}

// Convertir número a HEX
void u32_to_hex(uint32_t value, char *buf) {
    const char hex_digits[] = "0123456789ABCDEF";
    buf[0] = '0';
    buf[1] = 'x';
    for (int i = 0; i < 8; i++) {
        buf[2 + i] = hex_digits[(value >> (28 - i * 4)) & 0xF];
    }
    buf[10] = '\n';
    buf[11] = '\r';
    buf[12] = '\0';
}

void main(void) {
    volatile int32_t sw_value = 1;

    emu_gpio_init();            // Inicializa GPIO
    emu_gpio_write_port(sw_value);

    uart_puts("GPIO State: ");
    u32_to_hex(sw_value, wr_buffer);
    uart_puts(wr_buffer);

    uart_puts("Press u key to increment the counter\n");
    uart_puts("Press d key to decrement the counter\n");
    uart_puts("Press Ctrl+A C to exit qemu\n");

    while (1) {
        if (uart_tstc()) {
            char c = uart_getc();
            if (c == 'u') sw_value++;
            else if (c == 'd') sw_value--;

            if (sw_value > 0xFF) sw_value = 0xFF;
            if (sw_value < 0) sw_value = 0;

            emu_gpio_write_port(sw_value);

            uart_puts("GPIO State: ");
            u32_to_hex(sw_value, wr_buffer);
            uart_puts(wr_buffer);
        }
    }
}

