#include <string.h>

// TODO: possibly use glibc's implementation
size_t strlen(const char* string) {
	size_t result = 0;
	while (string[result])
		result++;
	return result;
}
