#include "terminal.h"

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x0F;

static void print_c(char c)
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
		term_row = VGA_ROWS - 1;
		memcpy((void *)vga_buffer, (void *)(vga_buffer + VGA_COLS), 2*VGA_COLS*(VGA_ROWS - 1));
		memset((void *)(vga_buffer + VGA_COLS*(VGA_ROWS - 1)), 0, 2*VGA_COLS);
	}
}

static void print_string(const char *str)
{
	for (size_t i = 0; str[i] != '\0'; ++i)
	{
		print_c(str[i]);
	}
}

static void print_number(uint64_t number)
{
	uint64_t n = number;
	if (n == 0)
	{
		print_c('0');
		return;
	}

	char num[20];
	memset(num, 0, 20);

	int i = 0;
	while (n > 0)
	{
		char digit = n % 10 + 0x30;
		num[i] = digit;
		++i;
		n = n / 10;
	}
	print_string(reverse(num));
}

static void print_hex_number(uint64_t number)
{
	uint64_t n = number;
	if (n == 0)
	{
		print_c('0');
		return;
	}

	char num[16];
	memset(num, 0, 16);

	int i = 0;
	while (n > 0)
	{
		char digit = 0;
		if (n % 16 < 10)
		{
			digit = n % 16 + 0x30;
		}
		else
		{
			digit = n % 16 - 10 + 0x41;
		}
		
		num[i] = digit;
		++i;
		n = n / 16;
	}
	print_string("0x");
	print_string(reverse(num));
}

void clear_screen()
{
	for (int i = 0; i < 2*VGA_ROWS; ++i)
	{
		printf("\n");
	}
}

void set_cursor(int x, int y)
{
	term_col = y;
	term_row = x;
}

void printf(const char *format, ...)
{
	va_list valist;

	va_start(valist, format);
	
	char last = 0;
	char current = 0;
	for (size_t i = 0; format[i] != '\0'; ++i)
	{
		current = format[i];
		if (current == '%' && last != '\\')
		{
			switch (format[++i])
			{
				case 'c':
					print_c(va_arg(valist, int));
					break;
				case 'd':
					print_number(va_arg(valist, uint64_t));
					break;
				case 'x':
					print_hex_number(va_arg(valist, uint64_t));
					break;
				case 's':
					print_string(va_arg(valist, char *));
					break;
				default:
					break;
			}
		}
		else
		{
			print_c(current);
		}
	}

	va_end(valist);

	return;
}
