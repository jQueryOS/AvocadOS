#ifndef _KERNEL_VGA_H
#define _KERNEL_VGA_H 1

typedef enum {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GREY = 7,
	DARK_GREY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_MAGENTA = 13,
	LIGHT_BROWN = 14,
	WHITE = 15,
} vga_color;

#include <stddef.h>
#include <stdint.h>

static inline uint8_t make_color(vga_color fg, vga_color bg) {
	return fg | bg << 4;
}

static inline uint16_t make_vgaentry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

#endif