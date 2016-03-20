#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <kernel/vga.h>
#include <kernel/tty.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
enum vga_color foreground;
enum vga_color background;

void terminal_initialize() {
	terminal_row = 0;
	terminal_column = 0;
	foreground = LIGHT_GREY;
	background = BLACK;
	terminal_color = make_color(foreground, background);
	terminal_buffer = VGA_MEMORY;
	size_t area = VGA_HEIGHT * VGA_WIDTH;
	for (size_t i = 0; i < area; i++) {
		terminal_buffer[i] = make_vgaentry(' ', terminal_color);
	}
}

void tempsetcolor(enum vga_color fg, enum vga_color bg) {
	terminal_color = make_color(fg, bg);
}

void setcolor(enum vga_color fg, enum vga_color bg) {
	tempsetcolor(fg, bg);
	foreground = fg;
	background = bg;
}

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

void putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void newline() {
	terminal_column = 0;
	if (++terminal_row == VGA_HEIGHT) {
		terminal_row = VGA_HEIGHT - 1;
		for (size_t y = 0; y < VGA_HEIGHT - 1; y++) {
			for (size_t x = 0; x < VGA_WIDTH; x++) {
				const size_t index = y * VGA_WIDTH + x;
				terminal_buffer[index] = terminal_buffer[index + VGA_WIDTH];
			}
		}
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = terminal_row * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(0, terminal_color);
		}
	}
}

void printchar(char c) {
	if (c  == '\n') {
		newline();
	} else {
		putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			newline();
		}
	}
}

void print(const char* text) {
	size_t datalen = strlen(text);
	for (size_t i = 0; i < datalen; i++)
		putchar(text[i]);
}

void println(const char* line) {
	print(line);
	newline();
}

//TODO: recursion is probably not the best way
void printnum(uint8_t number) {
	int next_digit = number / 10;
	if (next_digit) {
		printnum(next_digit);
	}
	putchar((char) (number % 10 + 48));
}

void print_special(enum vga_color color, const char* text, const char* message) {
	tempsetfg(color);
	print(text);
	resetfg();
	println(message);
}

void success(const char* message) {
	print_special(LIGHT_GREEN, "Success: ", message);
}

void info(const char* message) {
	print_special(LIGHT_BLUE, "Info: ", message);
}

void warn(const char* message) {
	print_special(LIGHT_BROWN, "Warning: ", message);
}

void err(const char* message) {
	print_special(LIGHT_RED, "Error: ", message);
}