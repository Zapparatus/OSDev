#include "kernel.h"

void kernel_main()
{
	init_idt();
	printf("Welcome to 64-bit long mode.\n");
	printf("This kernel has been booted using multiboot2.\n");
	printf("The kernel encountered no issues.\n");
	while (1) {}
}
