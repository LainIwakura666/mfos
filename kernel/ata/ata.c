#include "ata.h"

#define ATA_DATA      0x1F0
#define ATA_ERROR     0x1F1
#define ATA_SECTORS   0x1F2
#define ATA_LBA_LOW   0x1F3
#define ATA_LBA_MID   0x1F4
#define ATA_LBA_HIGH  0x1F5
#define ATA_DRIVE     0x1F6
#define ATA_STATUS    0x1F7
#define ATA_COMMAND   0x1F7

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}
static inline void insw(uint16_t port, void *addr, int cnt) {
    asm volatile("rep; insw" : "+D"(addr), "+c"(cnt) : "d"(port) : "memory");
}

int ata_read_sectors(uint32_t lba, uint8_t count, void *buffer) {

    while (inb(ATA_STATUS) & 0x80);

   // outb(ATA_DRIVE, 0xE0 | ((lba >> 24) & 0x0F));
    outb(ATA_DRIVE, 0xE0 | ((lba >> 24) & 0x0F) | 0x02);
    outb(ATA_SECTORS, count);
    outb(ATA_LBA_LOW, lba & 0xFF);
    outb(ATA_LBA_MID, (lba >> 8) & 0xFF);
    outb(ATA_LBA_HIGH, (lba >> 16) & 0xFF);

    outb(ATA_COMMAND, 0x20);

    for (int i = 0; i < count; i++) {
        while (1) {
            uint8_t status = inb(ATA_STATUS);
            if (!(status & 0x80) && (status & 0x08)) break;
        }

        insw(ATA_DATA, buffer, 256);
        buffer = (uint8_t *)buffer + 512;
    }
    return count;
}
