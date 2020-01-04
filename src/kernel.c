#include <stddef.h>
#include <stdint.h>
#include "idt.h"

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;
int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x0F;

void term_putc(char c)
{
	switch(c)
	{
		case '\n':
		{
			term_col = 0;
			++term_row;
			break;
		}
		default:
		{
			const size_t index = (VGA_COLS * term_row) + term_col;
			vga_buffer[index] = ((uint16_t)term_color << 8) | c;
			++term_col;
			break;
		}
	}
	if (term_col >= VGA_COLS)
	{
		term_col = 0;
		++term_row;
	}
	if (term_row >= VGA_ROWS)
	{
		term_col = 0;
		term_row = 0;
	}
}

void term_print(const char* str)
{
	for (size_t i = 0; str[i] != '\0'; ++i)
	{
		term_putc(str[i]);
	}
}
void term_println(const char* str)
{
	term_print(str);
	term_putc('\n');
}

char* reverse(char* str)
{
	int end = 0;
	while (str[end++] != 0) {}
	end -= 1;
	for (int i = 0; i < end/2; ++i)
	{
		char temp = str[i];
		str[i] = str[end - i - 1];
		str[end - i - 1] = temp;
	}
	return str;
}
void term_printn(uint64_t n)
{
	if (n == 0)
	{
		term_putc('0');
		return;
	}

	char num[20];
	for (int i = 0; i < 20; ++i)
	{
		num[i] = 0;
	}

	int i = 0;
	while (n > 0)
	{
		char digit = n % 10 + 0x30;
		num[i] = digit;
		++i;
		n = n / 10;
	}
	term_print(reverse(num));
}
void term_printnln(uint64_t n)
{
	term_printn(n);
	term_putc('\n');
}

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

void kernel_main()
{
	init_idt();
	term_println("Welcome to 64-bit long mode.");
	term_println("This kernel has been booted using multiboot2.");
	while (1) {}
}
