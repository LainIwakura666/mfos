#include <gdt.h>

void kernel_main(void) {
    init_gdt();
    while(1) {
        asm volatile("hlt");
    }
}
