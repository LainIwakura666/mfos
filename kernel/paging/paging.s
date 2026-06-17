.global enable_paging

enable_paging:
    mov 4(%esp), %eax
    mov %eax, %cr3

    mov %cr4, %eax
    orl  $0x00000010, %eax
    mov %eax, %cr4

    mov %cr0, %eax
    orl  $0x80000000, %eax
    mov %eax, %cr0

    jmp .Lflush
.Lflush:
    ret
