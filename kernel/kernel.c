#include 'kernel.h'

int main() {
    char* disp = (char *)VID_MEM;
    disp[0] = 'X';
    disp[1] = 0x09;

    // Shell goes here

}
