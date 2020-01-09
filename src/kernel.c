#include "kernel.h"

void kernel_main()
{
	clear_screen();
	set_cursor(0, 0);
	printf("The Kernel has started.\n");
	printf("Remapping paging structures...\n");
	load_paging_structure(create_paging_structures(0x1000));
	printf("Paging structures remapped.\n");
	printf("Initialized interrupts...\n");
	init_idt();
	printf("Interrupts initialized.\n");
	printf("Looping...\n");
	while (1) {}
}
