#include "common.h"
#include "terminal.h"

void panic(const char *message)
{
	printf(message);
	while (1) {}
}
