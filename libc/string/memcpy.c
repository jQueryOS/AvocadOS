#include <string.h>

void* memcpy(void* restrict destination_pointer, const void* restrict source_pointer, size_t size) {
	unsigned char* destination = (unsigned char*) destination_pointer;
	const unsigned char* source = (const unsigned char*) source_pointer;
	for (size_t i = 0; i < size; i++)
		destination[i] = source[i];
	return destination_pointer;
}
