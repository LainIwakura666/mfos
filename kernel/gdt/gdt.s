section .text

%define KERNEL_CODE_SELECTOR 0x08
%define KERNEL_DATA_SELECTOR 0x10

global gdt_flush
extern gdt_ptr

gdt_flush:
    lgdt [gdt_ptr]
    jmp KERNEL_CODE_SELECTOR:.flush_complete

.flush_complete:
    mov ax, KERNEL_DATA_SELECTOR
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
