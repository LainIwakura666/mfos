.global _start
_start:
    movb $'U', %al
    outb %al, $0xE9

    movl $1, %eax
    int $0x80

    jmp .
