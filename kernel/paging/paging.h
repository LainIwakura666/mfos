#ifndef PAGING_H
#define PAGING_H
#include <stdint.h>

void init_paging(void);
void map_user_page(uint32_t virt_addr, uint32_t phys_addr);

#endif
