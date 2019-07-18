// 'kernel_main' is external to this file
.extern kernel_main

// Make 'start' accessible outside this file
.global start

// The start of the multiboot header
// Magic flag for GRUB to detect kernel's location
.set MB_MAGIC, 0x1BADB002

// Load the modules on page boundaries and provide a memory map
.set MB_FLAGS, (1 << 0) | (1 << 1)

// Calculate a checksum for the previous values
.set MB_CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))

.section .multiboot
	.align 4
	.long MB_MAGIC
	.long MB_FLAGS
	.long MB_CHECKSUM

.section .bss
	.align 16
	stack_bottom:
		.skip 4096
	stack_top:

.section .text
	start:
		// Create the stack
		mov $stack_top, %esp

		// Go to kernel code
		call kernel_main

		// In case the kernel returns, hang
		hang:
			cli
			hlt
			jmp hang
