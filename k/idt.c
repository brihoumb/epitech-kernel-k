#include <stdio.h>
#include <k/kutils.h>

#include "io.h"
#include "idt.h"

static struct idt_r idtr;
extern unsigned long ticks;
static trap_inter_gate_t idt[256];

void idt_create_gate(u8 index,
		     u32 offset,
		     u16 selector,
		     u8 flags)
{
	idt[index].offset_low = offset & 0xFFFF;
	idt[index].segment = selector;
	idt[index].zero_set = 0;
	idt[index].flags = flags;
	idt[index].offset_high = (offset >> 16) & 0xFFFF;
}

void init_idt(void)
{
	idtr.base = (u32)idt;
	idtr.limit = sizeof(idt) - 1;

	for (unsigned int i = 0; i < 32; i++) {
		idt_create_gate(i, (u32)isr_map[i], 0x08, 0x8E);
		if (i < 16)
			idt_create_gate(32 + i, (u32)irq_map[i], 0x08, 0x8E);
	}
	__asm__ volatile("lidt %0\n":: "m" (idtr): "memory");
}

void generate_c_handler(const registers_t regs)
{
	if (regs.int_no < 32)
		printf("ERRCode: %d\r\n", regs.int_no);
	else {
		ticks++;
		if (regs.int_no == 32)
			gettick(); 
		else if (regs.int_no == 33)
			getkey();
		outb(0x20, 0x20);
	}
}
