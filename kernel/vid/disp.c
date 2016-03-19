// NOTE: THIS DOES NOT WORK AT THE MOMENT
#include "disp.h"

unsigned char* row_address(unsigned char l) {
    return (unsigned char*)0xC000 + ((l / 8) * 80) + ((l % 8) * 2048);
}
