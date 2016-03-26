#include <stdio.h>
#include <colors.h>

#if defined(__is_avocados_kernel)
#include <kernel/tty.h>
#endif

#if defined(__is_avocados_kernel)
const char* print_color(enum vga_color color, const char* text, const char* message) {
	tempsetfg(color);
	printf(text);
	resetfg();
	println(message);
	return message;
}
#else
#endif

const char* success(const char* message) {
#if defined(__is_avocados_kernel)
	print_color(LIGHT_GREEN, "Success: ", message);
#else
#endif
	return message;
}

const char* info(const char* message) {
#if defined(__is_avocados_kernel)
	print_color(LIGHT_BLUE, "Info: ", message);
#else
#endif
	return message;
}

const char* warn(const char* message) {
#if defined(__is_avocados_kernel)
	print_color(LIGHT_BROWN, "Warning: ", message);
#else
#endif
	return message;
}

const char* err(const char* message) {
#if defined(__is_avocados_kernel)
	print_color(LIGHT_RED, "Error: ", message);
#else
#endif
	return message;
}