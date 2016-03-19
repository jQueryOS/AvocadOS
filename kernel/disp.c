// no <stdio> :(
#include "disp.h"

unsigned char* row_address(unsigned char l) {
    return (unsigned char*)0xC000 + ((l / 8) * 80) + ((l % 8) * 2048);
}

int main(int argc, char *argv[]) {
    unsigned char* screen_index = (unsigned char*)0xC000;
    unsigned int byte_num = 0;
    unsigned int line_num = 0;

    // set screen mode
    _asm
        ld, a #0
        call #0xBC0E
    _endasm;

    // Screen constants

    for (line_num = 0; line_num < DISP_WIDTH; ; line_num++) {
        screen_index = row_address(line_num);

        for (byte_num = 0; byte_num < DISP_HEIGHT; byte_num++) {

            // render screen for pixel (byte_num, line_num)
            // screen_index[byte_num] = (unsigned char*)(/* 0 - 255*/)

        }
    }

    _asm
        call #0xBC0E
    _endasm;
}
