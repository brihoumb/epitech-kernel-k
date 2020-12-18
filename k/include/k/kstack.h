#include <k/types.h>

#ifndef KSTACK_H
#define KSTACK_H

void init_gdt(void);
void init_idt(void);
void init_pic(void);
void init_timer(void);
void switch_protect_mode(void);

#endif
