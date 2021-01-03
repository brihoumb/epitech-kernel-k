#include <k/types.h>

#ifndef GDT_H
#define GDT_H

struct gdt_r {
	u16 limit;
	u32 base;
} __attribute__((packed));

struct gdt_entry {
	u16 limit_15_0;
	u16 base_15_0;
	u8 base_23_16;
	u8 access;
	u8 limit_19_16:4;
	u8 granularity:4;
	u8 base_31_24;
} __attribute__((packed));

#endif
