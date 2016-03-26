#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H 1
 
#include <stddef.h>
#include <stdint.h>
#include <kernel/vga.h>

void terminal_initialize(void);
void terminal_putchar(char);
void terminal_write(const char*, size_t);
void terminal_writestring(const char*);

void tempsetcolor(vga_color, vga_color);
void setcolor(vga_color, vga_color);
void tempsetfg(vga_color);
void tempsetbg(vga_color);
void resetfg(void);
void resetbg(void);
void setfg(vga_color);
void setbg(vga_color);
void putentryat(char, uint8_t, size_t, size_t);
void newline(void);
void backspace(void);

#endif