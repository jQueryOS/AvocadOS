#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H
 
#include <stddef.h>
#include <stdint.h>
#include <kernel/vga.h>

void terminal_initialize(void);
void terminal_putchar(char);
void terminal_write(const char*, size_t);
void terminal_writestring(const char*);

void tempsetcolor(enum vga_color, enum vga_color);
void setcolor(enum vga_color, enum vga_color);
void tempsetfg(enum vga_color);
void tempsetbg(enum vga_color);
void resetfg(void);
void resetbg(void);
void setfg(enum vga_color);
void setbg(enum vga_color);
void putentryat(char, uint8_t, size_t, size_t);
void newline(void);

#endif