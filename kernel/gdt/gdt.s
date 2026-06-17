.set KERNEL_CODE_SELECTOR, 0x08
.set KERNEL_DATA_SELECTOR, 0x10

.global gdt_flush
.extern gdt_ptr

gdt_flush:
    lgdtl (gdt_ptr)
    ljmp $KERNEL_CODE_SELECTOR, $.Lflush

.Lflush:
    movw $KERNEL_DATA_SELECTOR, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    ret
