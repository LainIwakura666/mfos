AS = i686-elf-as
CC = i686-elf-gcc
LD = i686-elf-ld
OBJCOPY = i686-elf-objcopy

ASFLAGS = --32
CFLAGS = -m32 -ffreestanding -nostdlib -fno-stack-protector -fno-pic -O2 -Wall -Wextra
LDFLAGS = -m elf_i386 -T kernel/linker.ld -nostdlib

INCLUDES = -Ikernel -Ikernel/gdt -Ikernel/idt -Ikernel/paging -Ikernel/ata -Ikernel/load_user -Ikernel/lib -Ikernel/tss

KERNEL_C = kernel/kernel.c kernel/gdt/gdt.c kernel/idt/idt.c \
           kernel/paging/paging.c kernel/ata/ata.c \
           kernel/load_user/load_user.c kernel/lib/string.c \
           kernel/tss/tss.c
KERNEL_S = kernel/boot.s kernel/gdt/gdt_flush.s kernel/idt/isr.s \
           kernel/paging/enable_paging.s kernel/load_user/enter_user.s

KERNEL_OBJ = $(KERNEL_C:.c=.o) $(KERNEL_S:.s=.o)

USER_ASM = test/userprog.s
USER_BIN = test/userprog.bin

KERNEL_ELF = kernel/kernel.elf
OS_ISO = os.iso
PROG_IMG = prog.img
ISO_DIR = isodir

all: $(OS_ISO) $(PROG_IMG)

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(KERNEL_ELF): $(KERNEL_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

$(USER_BIN): $(USER_ASM)
	$(AS) $(ASFLAGS) $< -o test/userprog.o
	$(LD) -m elf_i386 -Ttext 0x400000 --oformat binary -o $@ test/userprog.o

$(OS_ISO): $(KERNEL_ELF) grub.cfg
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL_ELF) $(ISO_DIR)/boot/kernel.elf
	cp grub.cfg $(ISO_DIR)/boot/grub/grub.cfg
	grub-mkrescue -o $@ $(ISO_DIR)

$(PROG_IMG): $(USER_BIN)
	dd if=/dev/zero of=$@ bs=512 count=2048
	dd if=$(USER_BIN) of=$@ bs=512 seek=0 conv=notrunc

clean:
	rm -f $(KERNEL_OBJ) test/userprog.o $(KERNEL_ELF) $(USER_BIN) $(OS_ISO) $(PROG_IMG)
	rm -rf $(ISO_DIR)

run: all
	qemu-system-i386 -cdrom $(OS_ISO) -drive file=$(PROG_IMG),format=raw,if=ide,index=0 -debugcon stdio

.PHONY: all clean run
