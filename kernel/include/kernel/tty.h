#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H
 
#include <stddef.h>
#include <stdint.h>
#include <kernel/vga.h>
 
void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);

void tempsetcolor(enum vga_color fg, enum vga_color bg);
void setcolor(enum vga_color fg, enum vga_color bg);
void tempsetfg(enum vga_color color);
void tempsetbg(enum vga_color color);
void resetfg(void);
void resetbg(void);
void setfg(enum vga_color color);
void setbg(enum vga_color color);
void putentryat(char c, uint8_t color, size_t x, size_t y);
void newline(void);
void print(const char* text);
void println(const char* line);
void printnum(uint8_t number);
void print_special(enum vga_color color, const char* text, const char* message) ;
void success(const char* message);
void info(const char* message);
void warn(const char* message);
void err(const char* message);

#endif