#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void print(const char* data, size_t data_length) {
	for (size_t i = 0; i < data_length; i++)
		putchar((int) ((const unsigned char*) data)[i]);
}

//TODO: recursion is probably not the best way
static void printnum(int number) {
	int beheaded = number / 10;
	if (beheaded)
		printnum(beheaded);
	putchar(number % 10 + 48);
}

static int _printf(const char* restrict format, va_list parameters) {
	int written = 0;
	size_t amount;
	bool rejected_bad_specifier = false;

	while (*format != '\0') {
		if (*format != '%') {
		print_c:
			amount = 1;
			while (format[amount] && format[amount] != '%')
				amount++;
			print(format, amount);
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format;

		if (*(++format) == '%')
			goto print_c;

		if (rejected_bad_specifier) {
		incomprehensible_conversion:
			rejected_bad_specifier = true;
			format = format_begun_at;
			goto print_c;
		}

		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			print(&c, sizeof(c));
		} else if (*format == 's') {
			format++;
			const char* s = va_arg(parameters, const char*);
			print(s, strlen(s));
		} else if (*format == 'i') {
			//TODO: better format specifiers
			format++;
			int i = va_arg(parameters, int);
			printnum(i);
		} else
			goto incomprehensible_conversion;
	}
	return written;
} 

int printf(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);
	int written = _printf(format, parameters);
	va_end(parameters);

	return written;
}

int println(const char* restrict format, ...) {
	va_list parameters;
	va_start(parameters, format);
	int written = _printf(format, parameters);
	va_end(parameters);

	written += printf("\n");
	return written;
}