#include <string.h>

void* memmove(void* destination_pointer, const void* source_pointer, size_t size) {
	unsigned char* destination = (unsigned char*) destination_pointer;
	const unsigned char* source = (const unsigned char*) source_pointer;
	if (destination < source)
		for (size_t i = 0; i < size; i++)
			destination[i] = source[i];
	else
		for (size_t i = size - 1; i != (size_t) -1; i--)
			destination[i] = source[i];
	return destination_pointer;
}
