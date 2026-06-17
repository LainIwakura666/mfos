#include "paging.h"

#define PAGE_SIZE_4M  0x400000
#define PD_ENTRIES     1024
#define PDE_PRESENT    0x01
#define PDE_RW         0x02
#define PDE_4MB        0x80

static uint32_t page_directory[PD_ENTRIES] __attribute__((aligned(4096)));

extern void enable_paging(uint32_t pd_phys);

void init_paging(void) {

    for (uint32_t i = 0; i < PD_ENTRIES; ++i) {
        page_directory[i] = (i * PAGE_SIZE_4M) | PDE_PRESENT | PDE_RW | PDE_4MB;
    }

    uint32_t pd_phys = (uint32_t)page_directory;

    enable_paging(pd_phys);
}

void map_user_page(uint32_t virt_addr, uint32_t phys_addr) {
    uint32_t pde_index = virt_addr / PAGE_SIZE_4M;
    page_directory[pde_index] = phys_addr | PDE_PRESENT | PDE_RW | PDE_4MB | PDE_USER;

    asm volatile("invlpg (%0)" : : "r"(virt_addr) : "memory");
}
