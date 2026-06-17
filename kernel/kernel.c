#include "gdt.h"
#include "idt.h"
#include "paging.h"
#include "load_user.h"
#include "tss.h"

void kernel_main(void) {

    asm volatile("cli");
    init_gdt();
    init_idt();
    init_tss();
    init_paging();
    load_and_run_user();

    while(1) {
        asm volatile("hlt");
    }
}

