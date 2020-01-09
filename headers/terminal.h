#include "common.h"
#include "string.h"
#include "stdarg.h"

#define VGA_COLS 80
#define VGA_ROWS 25

static void print_c(char c);
static void print_number(uint64_t number);
static void print_hex_number(uint64_t number);
static void print_string(const char *str);

void set_cursor(int x, int y);
void clear_screen();

void printf(const char *format, ...);
