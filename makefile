# If the architecture is not x86_64 on linux
CC = ../x86_64-elf-4.9.1-Linux-x86_64/bin/x86_64-elf-gcc
LD = ../x86_64-elf-4.9.1-Linux-x86_64/bin/x86_64-elf-ld
# else
# CC = gcc
# LD = ld

CFLAGS = -std=gnu99 -ffreestanding
LDFLAGS = -n -nostdlib
QEMU = qemu-system-x86_64
ASMFLAGS = -felf64

all: bin/osdev.iso
bin/osdev.iso: bin/kernel.elf isoroot/boot/grub/grub.cfg
	@cp bin/kernel.elf isoroot/boot/
	@grub-mkrescue /usr/lib/grub/i386-pc isoroot -o bin/osdev.iso
obj/%.o: src/%.s
	@nasm $(ASMFLAGS) $< -o $@
obj/%.o: src/%.c
	@$(CC) $(CFLAGS) -Iheaders -c $< -o $@
bin/kernel.elf: obj/kernel.o obj/idt.o obj/terminal.o obj/string.o obj/io.o obj/panic.o obj/start.o
	@$(LD) $(LDFLAGS) -T linker.ld $^ -o $@

dev: bin/kernel.elf
	@$(QEMU) -kernel bin/kernel.elf --curses

run: bin/osdev.iso
	@$(QEMU) -drive file=bin/osdev.iso --curses

clean:
	@rm -f obj/*.o
	@rm -f bin/kernel.elf bin/osdev.iso
	@rm -f isoroot/boot/kernel.elf
