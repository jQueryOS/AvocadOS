#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>

#define TAB "    "
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
enum vga_color foreground;
enum vga_color background;
size_t area;
size_t all_but_last_line;

void terminal_initialize() {
	area = VGA_HEIGHT * VGA_WIDTH;
	all_but_last_line = area - VGA_WIDTH;
	terminal_row = 0;
	terminal_column = 0;
	foreground = LIGHT_GREY;
	background = BLACK;
	terminal_color = make_color(foreground, background);
	terminal_buffer = VGA_MEMORY;
	for (size_t i = 0; i < area; i++)
		terminal_buffer[i] = make_vgaentry(' ', terminal_color);
}

//TODO: support all escape chars, except \r. e.g. \b
void terminal_putchar(char c) {
	switch (c) {
		case '\n':
			newline();
			break;
		case '\t':
			terminal_writestring(TAB);
			break;
		default:
			putentryat(c, terminal_color, terminal_column, terminal_row);
			if (++terminal_column == VGA_WIDTH)
				newline();
			break;
	}
}

void terminal_write(const char* text, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(text[i]);
}

void terminal_writestring(const char* text) {
	terminal_write(text, strlen(text));
}

void tempsetcolor(enum vga_color fg, enum vga_color bg) {
	terminal_color = make_color(fg, bg);
}

void setcolor(enum vga_color fg, enum vga_color bg) {
	tempsetcolor(fg, bg);
	foreground = fg;
	background = bg;
}

//TODO: with_fg/bg macros?
void tempsetfg(enum vga_color color) {
	terminal_color = (terminal_color & 0xF0) | color;
}

void tempsetbg(enum vga_color color) {
	terminal_color = (terminal_color & 0x0F) | color << 4;
}

void resetfg() {
	tempsetfg(foreground);
}

void resetbg() {
	tempsetbg(background);
}

void setfg(enum vga_color color) {
	tempsetfg(color);
	foreground = color;
}

void setbg(enum vga_color color) {
	tempsetbg(color);
	background = color;
}

void putentryat(char c, uint8_t color, size_t left, size_t top) {
	const size_t i = top * VGA_WIDTH + left;
	terminal_buffer[i] = make_vgaentry(c, color);
}

void newline() {
	terminal_column = 0;
	if (++terminal_row != VGA_HEIGHT)
		return;
	terminal_row--;

	for (size_t i = 0; i < all_but_last_line; i++)
		terminal_buffer[i] = terminal_buffer[i + VGA_WIDTH];
	for (size_t i = all_but_last_line; i < area; i++)
		terminal_buffer[i] = make_vgaentry(' ', terminal_color);
}