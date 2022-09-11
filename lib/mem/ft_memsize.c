#include "lib_mem.h"
#include <stddef.h>

size_t ft_memsize(void *ptr)
{
	size_t size;
	byte *bytes;

	size = 0;
	bytes = ptr;
	while (bytes[size] != 0)
		size++;
	return size;
}
