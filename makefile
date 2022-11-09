# If the architecture is not x86_64 on linux
# CC = ../x86_64-elf-4.9.1-Linux-x86_64/bin/x86_64-elf-gcc
# LD = ../x86_64-elf-4.9.1-Linux-x86_64/bin/x86_64-elf-ld
# else
CC = gcc
LD = ld
QEMU = qemu-system-x86_64

CFLAGS = -std=gnu99 -ffreestanding -Wall
ASMFLAGS = -felf64
LDFLAGS = -n -nostdlib
QEMUFLAGS = -drive file=bin/osdev.iso

OBJECTS = obj/kernel.o \
	obj/start.o \
	obj/idt.o \
	obj/io.o \
	obj/memory.o \
	obj/panic.o \
	obj/string.o \
	obj/terminal.o

all: bin/osdev.iso
bin/osdev.iso: bin/kernel.elf isoroot/boot/grub/grub.cfg
	@cp bin/kernel.elf isoroot/boot/
	@grub-mkrescue /usr/lib/grub/i386-pc isoroot -o bin/osdev.iso
obj/%.o: src/%.s
	@nasm $(ASMFLAGS) $< -o $@
obj/%.o: src/%.c
	@$(CC) $(CFLAGS) -Iheaders -c $< -o $@
bin/kernel.elf: $(OBJECTS)
	@$(LD) $(LDFLAGS) -T linker.ld $^ -o $@

dev: bin/osdev.iso
	@$(QEMU) $(QEMUFLAGS) --curses

run: bin/osdev.iso
	@$(QEMU) $(QEMUFLAGS)

clean:
	@rm -f obj/*.o
	@rm -f bin/kernel.elf bin/osdev.iso
	@rm -f isoroot/boot/kernel.elf
