#include "lib_mem.h"

void *ft_memset(void *str, const int c, size_t n)
{
	byte *p;

	p = (byte *)str;
	while (n-- > 0)
		*p++ = c;
	return str;
}