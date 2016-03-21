#include <string.h>

int memcmp(const void* left_ptr, const void* right_ptr, size_t size) {
	const unsigned char* left = (const unsigned char*) left_ptr;
	const unsigned char* right = (const unsigned char*) right_ptr;
	for (size_t i = 0; i < size; i++)
		if (left[i] < right[i])
			return -1;
		else if (right[i] < left[i])
			return 1;
	return 0;
}
