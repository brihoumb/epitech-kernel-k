section .multiboot
multiboot_start:
    dd 0xe85250d6
    dd 0
    dd multiboot_end - multiboot_start
    dd 0x100000000 - (0xe85250d6 + 0 + (multiboot_end - multiboot_start))
    dw 0
multiboot_end:
    section .text
    global gdt_flush
    extern gp
gdt_flush:
    lgdt [gp]
    mov ax, 0x10
    mov ds, ax; This line restarts the computer
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2
flush2:
    ret               
    extern kernel_main
start:
    mov esp, stack_space
    call kernel_main
    hlt
    section .bss
    resb 10240
stack_space: