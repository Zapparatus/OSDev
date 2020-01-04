#include "kernel.h"

void kernel_main()
{
	init_idt();
	term_println("Welcome to 64-bit long mode.");
	term_println("This kernel has been booted using multiboot2.");
	while (1) {}
}
