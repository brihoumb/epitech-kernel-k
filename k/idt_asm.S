.macro isr_noerr num
.align 16
.global isr\num
isr\num:
	pushl $0
	pushl $\num
	jmp isr_create
.endm

.macro isr_err num
.align 16
.global isr\num
isr\num:
	pushl $\num
	jmp isr_create
.endm

.extern isr_handler
isr_create:
	pusha
	pushl %esp
	call generate_c_handler
	add $4, %esp
	popa
	add $8, %esp
	iret

.macro irq num, map
.global irq\num
irq\num:
	cli
	pushl $0
	pushl $\map
	jmp irq_stub
.endm


.extern irq_handler
irq_stub:
	pusha
	mov %ds, %ax
	pushl %eax
	movl %eax, %esi
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	call generate_c_handler
	pop %ebx
	movl %esi, %ebx
	movw %bx, %ds
	movw %bx, %es
	movw %bx, %fs
	movw %bx, %gs
	popa
	add $8, %esp
	iret
	
isr_noerr 0
isr_noerr 1
isr_noerr 2
isr_noerr 3
isr_noerr 4
isr_noerr 5
isr_noerr 6
isr_noerr 7
isr_err 8
isr_noerr 9
isr_err 10
isr_err 11
isr_err 12
isr_err 13
isr_err 14
isr_noerr 15
isr_noerr 16
isr_noerr 17
isr_noerr 18
isr_noerr 19
isr_noerr 20
isr_noerr 21
isr_noerr 22
isr_noerr 23
isr_noerr 24
isr_noerr 25
isr_noerr 26
isr_noerr 27
isr_noerr 28
isr_noerr 29
isr_noerr 30
isr_noerr 31

irq 0, 32
irq 1, 33
irq 2, 34
irq 3, 35
irq 4, 36
irq 5, 37
irq 6, 38
irq 7, 39
irq 8, 40
irq 9, 41
irq 10, 42
irq 11, 43
irq 12, 44
irq 13, 45
irq 14, 46
irq 15, 47
