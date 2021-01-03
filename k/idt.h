#include <k/types.h>

#ifndef ISR_IRQ_ASM_H
#define ISR_IRQ_ASM_H

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif

#ifndef IDT_H
#define IDT_H

typedef struct registers
{
    u32 ds;
    u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    u32 int_no, err_code;
    u32 eip, cs, eflags, useresp, ss;
} registers_t;

struct idt_r {
	u16 limit;
	u32 base;
} __attribute__((packed));

typedef struct trap_inter_gate {
	u16 offset_low;
	u16 segment;
	u8 zero_set;
	u8 flags;
	u16 offset_high;
} __attribute__((packed)) trap_inter_gate_t;

typedef void (*func)(void);

func isr_map[] = {
	&isr0, &isr1, &isr2, &isr3, &isr4, &isr5, &isr6, &isr7,
	&isr8, &isr9, &isr10, &isr11, &isr12, &isr13, &isr14, &isr15,
	&isr16, &isr17, &isr18, &isr19, &isr20, &isr21, &isr22, &isr23,
	&isr24, &isr25, &isr26, &isr27, &isr28, &isr29, &isr30, &isr31
};

func irq_map[] = {
	&irq0, &irq1, &irq2, &irq3, &irq4, &irq5, &irq6, &irq7,
	&irq8, &irq9, &irq10, &irq11, &irq12, &irq13, &irq14, &irq15
};

#endif
