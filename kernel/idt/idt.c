#include "idt.h"
#include "gdt.h"

#define IDT_ENTRIES 256

static struct idt_entry idt[IDT_ENTRIES];
static struct idt_ptr   idt_ptr;

extern void isr_default();
extern void isr_syscall();

static void idt_set_entry(int num, uint32_t handler, uint16_t sel, uint8_t flags) {
    idt[num].base_low  = handler & 0xFFFF;
    idt[num].base_high = (handler >> 16) & 0xFFFF;
    idt[num].selector  = sel;
    idt[num].zero      = 0;
    idt[num].flags     = flags;
}

void init_idt() {
    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt_set_entry(i, (uint32_t)isr_default, KERNEL_CS, 0x8E);
    }

    idt_set_entry(0x80, (uint32_t)isr_syscall, KERNEL_CS, 0xEE);

    idt_ptr.limit = sizeof(struct idt_entry) * IDT_ENTRIES - 1;
    idt_ptr.base  = (uint32_t)idt;
    asm volatile("lidt %0" : : "m"(idt_ptr));
}
