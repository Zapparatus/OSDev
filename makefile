i686-elf	:= ../i686-elf-4.9.1-Linux-x86_64/bin

all: bin/osdev.iso
bin/osdev.iso: bin/kernel.elf isoroot/boot/grub/grub.cfg
	cp bin/kernel.elf isoroot/boot/
	grub-mkrescue isoroot -o bin/osdev.iso
obj/%.o: src/%.s
	$(i686-elf)/i686-elf-gcc -std=gnu99 -ffreestanding -g -c $< -o $@
obj/%.o: src/%.c
	$(i686-elf)/i686-elf-gcc -std=gnu99 -ffreestanding -g -c $< -o $@
bin/kernel.elf: obj/kernel.o obj/start.o
	$(i686-elf)/i686-elf-gcc -ffreestanding -nostdlib -g -T linker.ld obj/start.o obj/kernel.o -o bin/kernel.elf -lgcc

dev: bin/kernel.elf
	qemu-system-i386 -kernel bin/kernel.elf --curses

run: bin/osdev.iso
	qemu-system-i386 -drive file=bin/osdev.iso --curses

clean:
	rm -rf obj/*
	rm -rf bin/*
	rm -r isoroot/boot/kernel.elf
