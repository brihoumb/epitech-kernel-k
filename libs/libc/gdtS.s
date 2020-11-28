/* This will set up our new segment registers.  We need to do
 something special in order to set CS.  We do what is called
; a far jump.  A jump that includes a segment as well as an
; offset.  This is declared in C as 'extern void gdt_flush();'*/

#include <gdt.h>

.extern printf
.section .data

hello:
    .string "Hello!\r\n"

.section .text

.global _gdt_flush
.extern _gp
_gdt_flush:
	lgdt _gp	/* Load the GDT with our '_gp' which is a special pointer*/
	mov %ax, 0x10
	mov %ds, %ax
	mov %es, %ax
	mov %fs, %ax
	mov %gs, %ax
	mov %ss, %ax
	mov %esp, 0x2ffff  /* Necessary ? Set stack to grown downwards from 0x30000 */
	ret

.global _tss_flush
_tss_flush:
	mov %ax, 0x2B
	ltr %ax
	ret

.global _enter_protected
_enter_protected:
	mov		%eax, %cr0
	or		%eax, 1
	mov		%cr0, %eax
	ret

.global _start_kernel
_start_kernel:
	.byte 0x66
	.byte 0xEA
	.int  0x20000
	.word 0x0008
	ret
