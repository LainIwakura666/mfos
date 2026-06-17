#ifndef PAGING_H
#define PAGING_H
#include <stdint.h>

#define PDE_PRESENT 0x01
#define PDE_RW      0x02
#define PDE_USER    0x04
#define PDE_4MB     0x80

void init_paging(void);
void map_user_page(uint32_t virt_addr, uint32_t phys_addr);

#endif
