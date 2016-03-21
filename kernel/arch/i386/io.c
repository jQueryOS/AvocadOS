#include <kernel/io.h>
#include <kernel/vga.h>

void io_initialize() {
	//ensure scancode set #1
	outb(0x60, 0xf0);
	outb(0x60, 1);
}

void update_cursor(int row, int column)
{
	unsigned short position = (row * VGA_WIDTH) + column;

	// cursor LOW port to vga INDEX register
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(position & 0xFF));
	// cursor HIGH port to vga INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char)((position >> 8) & 0xFF));
}

const char* scancode = "\0\x10""1234567890-=\b\tQWERTYUIOP[]\n\x1d""ASDFGHJKL;'`\x1e\\ZXCVBNM,./\x1d*\x1e \x1f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x9c\x9d\x97\x98\x99\x9a\x94\x95\x96\x9b\x91\x92\x93\x90\x9a\0\0\0\x1b\x1c";
//TODO: handle 0xe0 chars, wrapper class
/*
somebody's laptop (if tested, please confirm) - ctrl + alt + f1, showkey --scancodes, ctrl + alt + f7
help e0 5b 3b e0 db
dim e0 4c
bright e0 54
screenthing 
mute 
quiet 
loud 
media back 
media play/pause e0 22 e0 a2
media forward 
aeroplane mode 
*/
//set 2 - keep in case it is needed
//const char* scancode = "\x19\0\x15\x13\x11\x12\x1c\0\x1a\x18\x16\x14\t`\0\0\x1f\x1e\x1dQ1\0\0\0ZSAW2\0\0CXDE43\0\0 VFTR5\0\0NBHGY6\0\0\0MJU78\0\0,KIO09\0\0./L;P-\0\0\0'\0[=\0\0\x9e\x9f\n]\0\\\0\0\0\0\b\0\0\x91\0\x94\x97\0\0\0\x90\x9a\x92\x95\x96\x98\x10\xa0"
/*
\0 invalid
10 esc
11-1c f1-f12
1d lctrl
1e lshift
1f lalt
90-99 numpad0-9
9a .
9b -
9c +
9f rshift
//a0 numlock
//a1 scroll lock
//a2 caps
*/
char io_getscancode() {
    char c = 0;
    do {
        if(inb(0x60) != c) {
            c = inb(0x60);
            if (c > 0)
                return c;
        }
    } while(1);
}

char io_getchar() {
	int code = io_getscancode();
	//TODO: special chars - how can we fit them? the current way won't work because of release
	//if (code & scancode[code])
	//	return //special
	//TODO:keep upper bit - signifies release:
	//return (scancode[code & 0x7F] | (code & 0x80));
	//bool release = code & 0x80 ? true : false;
	//int character = code & 0x7e;
	//if (character >= 0x1d && character <= 0x1f)
	if (code & 0x80)
		return '\xFF';
    return scancode[code];
}

bool ctrl;
bool shift;
bool alt;

//TODO: use this to handle interrupts
key io_getkey() {
	key returns = {};
	return returns;
}