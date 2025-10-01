#define UART0 0x10000000L

static inline void putchar(char c) {
    volatile char *uart = (char *)UART0;
    *uart = c;
}

void print(const char *s) {
    while (*s) {
        putchar(*s++);
    }
}
