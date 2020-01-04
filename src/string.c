#include "string.h"

void *memset(void *str, int c, size_t n)
{
  for (size_t i = 0; i < n; ++i)
  {
    ((char *)str)[i] = (char)c;
  }

  return str;
}

size_t strlen(const char *str)
{
  size_t i = 0;
  while (str[i++] != 0) {}
  return i - 1;
}

char *reverse(char *str)
{
  size_t len = strlen(str);
  char temp = 0;
  for (size_t i = 0; i < len/2; ++i)
  {
    temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
  }

  return str;
}
