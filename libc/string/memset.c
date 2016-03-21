#include <string.h>

void* memset(void* buffer_pointer, int value, size_t size) {
	unsigned char* buffer = (unsigned char*) buffer_pointer;
	for (size_t i = 0; i < size; i++)
		buffer[i] = (unsigned char) value;
	return buffer_pointer;
}
