#include <stdint.h>

void gdt_set_gate(int, unsigned long, unsigned long, unsigned char, unsigned char);
void gdt_install();

/* Descripteur de segment */
struct gdtdesc {
    uint16_t    limit_low;
    uint16_t    base_low;
    uint8_t     base_middle;
    uint8_t     access;
    uint8_t     granularity;
    uint8_t     base_high;
} __attribute__ ((packed));

/* Registre GDTR */
struct gdtr {
    uint16_t limit ;
    uint32_t base ;
} __attribute__ ((packed));