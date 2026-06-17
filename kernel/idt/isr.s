.global isr_default
.global isr_syscall

isr_default:
    movb $'!', %al
    outb %al, $0xE9
    cli
    hlt
    iret

isr_syscall:
    push %eax

    cmpl $1, %eax
    jne 1f

    movb $'E', %al
    outb %al, $0xE9
    cli
    hlt

    pop %eax
    iret

1:
    movb $'?', %al
    outb %al, $0xE9
    pop %eax
    iret
