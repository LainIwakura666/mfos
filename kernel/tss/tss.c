#include "tss.h"
#include "gdt.h"

static struct tss_entry tss;

extern void gdt_set_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

void init_tss(void) {

    uint8_t *p = (uint8_t *)&tss;
    for (unsigned i = 0; i < sizeof(tss); i++)
        p[i] = 0;


    tss.ss0  = KERNEL_DS;
    tss.esp0 = 0x00100000;

    tss.iomap_base = sizeof(struct tss_entry);

    gdt_set_entry(5, (uint32_t)&tss, sizeof(struct tss_entry) - 1, 0x89, 0x00);

    asm volatile("mov $0x28, %%ax; ltr %%ax" : : : "eax");
}
