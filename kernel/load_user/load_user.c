#include "ata.h"
#include "paging.h"
#include "string.h"

extern void enter_user_mode(uint32_t entry, uint32_t stack_top);

#define USER_CODE_ADDR  0x400000
#define USER_STACK_ADDR 0x7FC00000
#define USER_STACK_TOP  (USER_STACK_ADDR + 0x400000U - 16)

void load_and_run_user(void) {

    uint8_t *prog = (uint8_t*)USER_CODE_ADDR;
    ata_read_sectors(0, 1, prog);

    map_user_page(USER_CODE_ADDR, USER_CODE_ADDR);
    map_user_page(USER_STACK_ADDR, USER_STACK_ADDR);

    asm volatile("sti");

    enter_user_mode(USER_CODE_ADDR, USER_STACK_TOP);
}
