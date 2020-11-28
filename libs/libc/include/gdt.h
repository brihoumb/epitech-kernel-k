#ifndef GDT_H_
# define GDT_H_

typedef unsigned long int addr;

extern void _gdt_flush();
extern void _tss_flush();
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();
extern void _enter_protected();
extern void _start_kernel();

#define SEG_DESCTYPE(x)  ((x) << 0x04) // Descriptor type (0 for system, 1 for code/data)
#define SEG_PRES(x)      ((x) << 0x07) // Present
#define SEG_SAVL(x)      ((x) << 0x0C) // Available for system use
#define SEG_LONG(x)      ((x) << 0x0D) // Long mode
#define SEG_SIZE(x)      ((x) << 0x0E) // Size (0 for 16-bit, 1 for 32)
#define SEG_GRAN(x)      ((x) << 0x0F) // Granularity (0 for 1B - 1MB, 1 for 4KB - 4GB)
#define SEG_PRIV(x)     (((x) &  0x03) << 0x05)   // Set privilege level (0 - 3)
 
#define SEG_DATA_RD        0x00 // Read-Only
#define SEG_DATA_RDA       0x01 // Read-Only, accessed
#define SEG_DATA_RDWR      0x02 // Read/Write
#define SEG_DATA_RDWRA     0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD    0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA   0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD  0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA 0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX        0x08 // Execute-Only
#define SEG_CODE_EXA       0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD      0x0A // Execute/Read
#define SEG_CODE_EXRDA     0x0B // Execute/Read, accessed
#define SEG_CODE_EXC       0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA      0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC     0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA    0x0F // Execute/Read, conforming, accessed

#define	GDT_CODE_PL0	SEG_DESCTYPE(1)	| SEG_PRES(1)	| SEG_SAVL(0) |	\
						SEG_LONG(0)		| SEG_SIZE(1)	| SEG_GRAN(1) |	\
						SEG_PRIV(0)		| SEG_CODE_EXRD
 
#define GDT_DATA_PL0	SEG_DESCTYPE(1)	| SEG_PRES(1)	| SEG_SAVL(0) | \
						SEG_LONG(0)		| SEG_SIZE(1)	| SEG_GRAN(1) | \
						SEG_PRIV(0)		| SEG_DATA_RDWR
 
#define GDT_CODE_PL3	SEG_DESCTYPE(1)	| SEG_PRES(1)	| SEG_SAVL(0) | \
						SEG_LONG(0)		| SEG_SIZE(1)	| SEG_GRAN(1) | \
						SEG_PRIV(3)		| SEG_CODE_EXRD
 
#define GDT_DATA_PL3	SEG_DESCTYPE(1)	| SEG_PRES(1)	| SEG_SAVL(0) | \
						SEG_LONG(0)		| SEG_SIZE(1)	| SEG_GRAN(1) | \
						SEG_PRIV(3)		| SEG_DATA_RDWR

typedef volatile struct tss
{
	unsigned short link;
	unsigned short link_h;

	unsigned long esp0;
	unsigned short ss0;
	unsigned short ss0_h;

	unsigned long esp1;
	unsigned short ss1;
	unsigned short ss1_h;

	unsigned long esp2;
	unsigned short ss2;
	unsigned short ss2_h;

	unsigned long cr3;
	unsigned long eip;
	unsigned long eflags;

	unsigned long eax;
	unsigned long ecx;
	unsigned long edx;
	unsigned long ebx;

	unsigned long esp;
	unsigned long ebp;
	
	unsigned long esi;
	unsigned long edi;

	unsigned short es;
	unsigned short es_h;

	unsigned short cs;
	unsigned short cs_h;

	unsigned short ss;
	unsigned short ss_h;

	unsigned short ds;
	unsigned short ds_h;

	unsigned short fs;
	unsigned short fs_h;

	unsigned short gs;
	unsigned short gs_h;

	unsigned short ldt;
	unsigned short ldt_h;

	unsigned short trap;
	unsigned short iomap;
} __attribute__((packed)) tss_t;

/* TSS.C */
//extern void tss_set_kernel_stack(unsigned int stack);
//extern void tss_install(signed int num, unsigned short ss0, unsigned short esp0);
//extern void tss_switch();



typedef     unsigned char       uint8_t;
typedef     unsigned short      uint16_t;
typedef     unsigned long       uint32_t;
typedef     unsigned long long  uint64_t;
/*
#define 	GDT_ENTRY_BOOT_CS   2;
#define 	GDT_ENTRY_BOOT_DS   3;
#define 	GDT_ENTRY_BOOT_TSS  4;

#define 	GDT_ENTRY_KERNEL_CS 2;
#define 	GDT_ENTRY_KERNEL_DS 3;



 typedef struct gdt_entry {
        uint16_t    limit;
        uint16_t    base0_15;
        uint8_t     base16_23;
        uint8_t     attribs0_7;  //!< P(1bit) | DPL(2bit) | S(1bit) | Type(4bit)
        uint8_t     attribs8_15; //!< G(1bit) | D/B(1bit) | 0(1bit) | AVL(1bit) | limit16_19(4bit)
        uint8_t     base24_31;
} __attribute__ ((packed)) gdt_entry_t;

struct gdt_ptr {
	uint16_t len;
	unsigned int ptr;
} __attribute__((packed));

static inline void wrfs32(unsigned int v, unsigned int addr)
{
	asm volatile("movl %1,%%fs:%0" : "+m" (*(unsigned int *)addr) : "ri" (v));
}
*/


#endif /* GDT_H_ */