#include "kernel.h"

void kernel_main()
{
	clear_screen();
	set_cursor(0, 0);
	printf("Kernel starting...\n");
	printf("Loading interrupts...\n");
	init_idt();
	printf("Interrupts loaded.\n");
	printf("Looping...\n");
	while (1) {}
}
