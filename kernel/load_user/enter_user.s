.global enter_user_mode

enter_user_mode:
    mov 4(%esp), %eax
    mov 8(%esp), %edx

    mov $0x23, %ecx
    movw %cx, %ds
    movw %cx, %es
    movw %cx, %fs
    movw %cx, %gs

    pushfl
    pop %ecx
    orl $0x3000, %ecx
    push %ecx

    pushl $0x23
    push %edx
    push %ecx
    pushl $0x1B
    push %eax

    iret
