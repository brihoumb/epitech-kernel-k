#include "io.h"

#define COM1 0x3F8

void init_serial(void)
{
	outb(COM1 + 1, 0x00);
	outb(COM1 + 3, 0x80);
	outb(COM1, 0x03);
	outb(COM1 + 1, 0x00);
	outb(COM1 + 3, 0x03);
	outb(COM1 + 2, 0xC7);
}

int write(const void *s, size_t length)
{
	size_t bytes = 0;

	for (size_t i = 0; i < length; i++) {
		outb(COM1, *(int*)s++);
		bytes++;
	}
	return (bytes);
}
