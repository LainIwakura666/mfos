#include "gdt.h"
#include "idt.h"
#include "paging.h"
#include "load_user.h"

void kernel_main(void) {

    init_gdt();
    init_idt();
    init_paging();
    load_and_run_user();

    while(1) {
        asm volatile("hlt");
    }
}

