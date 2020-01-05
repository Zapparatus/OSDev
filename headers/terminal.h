#include "common.h"
#include "string.h"
#include "stdarg.h"

static void print_c(char c);
static void print_number(uint64_t number);
static void print_hex_number(uint64_t number);
static void print_string(const char *str);

void printf(const char *format, ...);
