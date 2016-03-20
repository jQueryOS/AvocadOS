#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>

#if defined(__linux__)
#error "Use a cross-compiler"
#endif

#if !defined(__i386__)
#error "This needs to be compiled with an ix86-elf compiler"
#endif

// TODO: possibly use glibc's implementation
size_t strlen(const char* str) {
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

void kernel_early(void) {
	terminal_initialize();
}

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main() {
	/* Initialize terminal interface */
	terminal_initialize();
	println("Hello, World!");
	for(uint8_t i = 0; i <=50; i++) {
		printnum(i);
		newline();
	}
	success("Test.");
	info("Test.");
	warn("Test.");
	err("Test.");
}
