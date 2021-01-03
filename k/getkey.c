#include <stdio.h>

#include "io.h"
#include "keyboard.h"

int getkey(void) {
	int keycode = 0;
	unsigned char c = 0;
	unsigned char status = 0;

	outb(0x20, 0x20);
	status = inb(0x64);
	if (status & 0x01) {
		keycode = inb(0x60);
		if (keycode < 0) {
			return (-1);
		}
		c = keyboard[keycode];
		printf("%c\r\n", c);
		return (c);
	}
	return (-1);
}
