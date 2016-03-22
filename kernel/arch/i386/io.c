#include <utils.h>

#include <kernel/io.h>
#include <kernel/vga.h>

#include <kernel/tty.h>

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

const char* scancode = "\x01\x10""1234567890-=\b\tqwertyuiop[]\n\x1d""asdfghjkl;'`\x1e\\zxcvbnm,./\x1d*\x1e \x1f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x7c\x7d\x77\x78\x79\x7a\x74\x75\x76\x7b\x71\x72\x73\x70\x7a\x01\0\x01\x1b\x1c";
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
//const char* scancode = "\x19\x01\x15\x13\x11\x12\x1c\x01\x1a\x18\x16\x14\t`\x01\0\x1f\x1e\x1dQ1\x01\0\0ZSAW2\x01\0CXDE43\x01\0 VFTR5\x01\0NBHGY6\x01\0\0MJU78\x01\0,KIO09\x01\0./L;P-\x01\0\0'\0[=\x01\0\x7e\x7f\n]\x01\\\x01\0\x01\0\b\x01\0\x71\x01\x74\x77\x01\0\x01\x70\x7a\x72\x75\x76\x78\x10\xa0"
/*
01 invalid
10 esc
11-1c f1-f12
1d lctrl
1e lshift
1f lalt
70-79 numpad0-9
7a .
7b -
7c +
7f rshift
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

bool ctrl;
bool shift;
bool alt;

char io_getchar() {
	key result = {};
	while (!result.press || result.ctrl || result.alt) {
		result = io_getkey();
	}
	return result.character;
}

//TODO: use interrupts
key io_getkey() {
	int code = 0;
	while (!code) {
		int code = io_getscancode();
		bool press = code & 0x80 ? false : true;
		int character = scancode[code & 0x7f];
		switch (character) {
			case 0x1d: case 0x7d: ctrl = press; code = 0; continue;
			case 0x1e: case 0x7e: shift = press; code = 0; continue;
			case 0x1f: case 0x7f:  alt = press; code = 0; continue;
		}
		if (shift && !alt && !ctrl)
			character = shiftify(character);
		key result = { .character = character, .press = press, .ctrl = ctrl, .shift = shift, .alt = alt };
	    return result;
	}
	return (key) {};
}