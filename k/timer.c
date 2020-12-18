#include "io.h"

unsigned long ticks = 0;

void init_timer(void)
{
	u32 divider = 1193182 / 100;
	u8 lsb = (u8)(divider & 0xff);
	u8 msb = (u8)((divider >> 8) & 0xff);

	outb(0x42, 0x36);
	outb(0x40, lsb);
	outb(0x40, msb);
	outb(0x20, 0x20);
}

unsigned long gettick()
{
	return ticks;
}
