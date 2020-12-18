#include <k/kutils.h>

#include "gdt.h"

struct gdt_r gdtr;
struct gdt_entry gdt[5];

void init_gdt_entry(u32 base,
		    u32 limit,
		    u8 access,
		    u8 granularity,
		    struct gdt_entry *gdt)
{
	gdt->limit_15_0 = (limit & 0xffff);
	gdt->base_15_0 = (base & 0xffff);
	gdt->base_23_16 = (base & 0xf0000) >> 16;
	gdt->access = access;
	gdt->granularity = granularity;
	gdt->limit_19_16 = (limit & 0xf0000) >> 16;
	gdt->base_31_24 = (base & 0xff000000) >> 24;
}

void init_gdt(void)
{
	init_gdt_entry(0x0, 0x0, 0x0, 0x0, &gdt[0]);
	init_gdt_entry(0x0, 0xfffff, 0x9b, 0x0d, &gdt[1]);
	init_gdt_entry(0x0, 0xfffff, 0x93, 0x0d, &gdt[2]);
	init_gdt_entry(0x0, 0xfffff, 0xff, 0x0d, &gdt[3]);
	init_gdt_entry(0x0, 0xfffff, 0xf3, 0x0d, &gdt[4]);
	gdtr.base = (u32)gdt;
	gdtr.limit = sizeof(gdt) - 1;
	asm volatile("lgdt %0\n":: "m" (gdtr): "memory");
}

void switch_protect_mode(void)
{
	write("", 1);
	__asm__(
		"mov %eax, %cr0\n"
		"or %eax, 1\n"
		"mov %cr0, %eax\n"
		"movw $0x10, %ax\n"
		"movw %ax, %ds\n"
		"movw %ax, %fs\n"
		"movw %ax, %gs\n"
		"movw %ax, %ss\n"
		"movw %ax, %es\n"
		"pushl $0x08\n"
		"pushl $1f\n"
		"lret\n"
		"1:\n"
	);
}
