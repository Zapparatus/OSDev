#include "common.h"
#include "string.h"
#include "stdarg.h"

#define VGA_COLS 80
#define VGA_ROWS 25

void set_cursor(int x, int y);
void clear_screen();

void printf(const char *format, ...);
