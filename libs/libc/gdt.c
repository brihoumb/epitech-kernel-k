#include <string.h>
#include <stdio.h>
#include "gdt.h"

tss_t sys_tss;

struct gdt_entry
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

struct gdt_entry gdt[5];
struct gdt_ptr _gp;

//extern void _gdt_flush();
//extern void _tss_flush();

void gdt_set_gate(int num, unsigned long base,
unsigned long limit, unsigned char access, unsigned char gran)
{
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;

	gdt[num].limit_low = (limit & 0xFFFF);
	gdt[num].granularity = ((limit >> 16) & 0x0F);

	gdt[num].granularity |= (gran & 0xF0);
	gdt[num].access = access;
}

void tss_install(signed int num, unsigned short ss0, unsigned short esp0)
{
	addr base = (addr)&sys_tss;
	addr size = base + sizeof(tss_t);

	gdt_set_gate(num, base, size, 0xE9, 0x00);

	memset((void *)&sys_tss, 0, sizeof(sys_tss));

	sys_tss.ss0	= ss0;
	sys_tss.esp0	= esp0;

	sys_tss.cs = 0x0B;
	sys_tss.ss = sys_tss.ds = sys_tss.es = sys_tss.fs = sys_tss.gs = 0x13;
}


void gdt_install()
{
	printf("0\n");
	_gp.limit = (sizeof(struct gdt_entry) * 6) - 1;
	_gp.base = (addr)&gdt;
	printf("1\n");

	gdt_set_gate(0, 0, 0, 0, 0);
	printf("2\n");

	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	printf("3 %X\n", GDT_CODE_PL0);

	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	printf("4 %X\n", GDT_DATA_PL0);

	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	printf("5 %X\n", GDT_CODE_PL3);

	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
	printf("6 %X\n", GDT_DATA_PL3);

	tss_install(5, 0x10, 0x0);
	printf("7\n");

	_enter_protected();
	printf("8\n");

	_gdt_flush();
	printf("9\n");

//	_tss_flush();
	printf("10\n");

//	_start_kernel();
	printf("11\n");
}


/*
struct gdtdesc {
    uint16_t lim0_15;    
    uint16_t base0_15;
    uint8_t base16_23;
    uint8_t acces;
    uint8_t lim16_19 : 4;
    uint8_t other : 4;
    uint8_t base24_31;
} __attribute__ ((packed));


struct gdtr {
    uint16_t limite;
    uint32_t base;
} __attribute__ ((packed));

#define GDT_BASE 0
#define GDT_SIZE 0xffffffff

struct gdtdesc kgdt[6];
struct gdtr kgdtr;

void init_gdt_desc(uint32_t base, uint32_t limite, uint8_t acces, uint8_t other,
                   struct gdtdesc *desc)
{
    desc->lim0_15 = (limite & 0xffff);
    desc->base0_15 = (base & 0xffff);
    desc->base16_23 = (base & 0xff0000) >> 16;
    desc->acces = acces;
    desc->lim16_19 = (limite & 0xf0000) >> 16;
    desc->other = (other & 0xf);
    desc->base24_31 = (base & 0xff000000) >> 24;
    return;
}

void gdt_install()
{

	printf("oui\n");

    init_gdt_desc(0x0, 0x0, 0x0, 0x0, &kgdt[0]);
    init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &kgdt[1]);
    init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &kgdt[2]);
    init_gdt_desc(0x0, 0xFFFFF, 0xFB, 0x0D, &kgdt[3]);
    init_gdt_desc(0x0, 0xFFFFF, 0xF3, 0x0D, &kgdt[4]);
    init_gdt_desc(0x0, 0x0, 0xF7, 0x0D, &kgdt[5]);

	printf("oui2\n");

    kgdtr.limite = GDT_SIZE * 8;
    kgdtr.base = GDT_BASE;

    memcpy((char *) kgdtr.base, (char *) kgdt, kgdtr.limite);

    asm("lgdtl (kgdtr)");

    asm("   movw $0x10, %ax \n \
        movw %ax, %ds       \n \
        movw %ax, %es       \n \
        movw %ax, %fs       \n \
        movw %ax, %gs       \n \
        ljmp $0x08, $next   \n \
        next:               \n");

    asm("   movw $0x18, %ax \n \
            movw %ax, %ss \n \
            movl $0x20000, %esp");

}
*/