#if !defined(__cplusplus)
#include <stdbool.h> //C doesn't have booleans by default
#endif
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <colors.h>

#include <kernel/tty.h>
#include <kernel/io.h>

#if defined(__linux__)
#error "Use a cross-compiler"
#endif

#if !defined(__i386__) && !defined(__i686__)
#error "This needs to be compiled with an ix86-elf compiler"
#endif

void kernel_early() {
	terminal_initialize();
}

#if defined(__cplusplus)
extern "C" //C linkage
#endif
void kernel_main() {
	terminal_initialize();
	io_initialize();
	println("Hello, World!");
	for(int i = 1; i <= 30; i++)
		println("%i", i);
	success("Test.");
	info("Test.");
	warn("Test.");
	err("Test\ttabs.");
	while (true) {
		//io_getchar();
		println("%c", io_getchar());
	}
}