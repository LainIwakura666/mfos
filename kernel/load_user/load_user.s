.global enter_user_mode

enter_user_mode:
    mov 4(%esp), %eax
    mov 8(%esp), %edx

    movw $0x23, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    pushl $0x23
    push %edx
    pushfl
    pushl $0x1B
    push %eax

    iret
