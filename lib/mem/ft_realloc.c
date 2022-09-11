#include "lib_mem.h"
#include <stddef.h>
#include <stdlib.h>

void *ft_realloc(void *src, const size_t size)
{
	void *dst;
	size_t mem_size;

	if (size == 0)
	{
		ft_memdel(&src);
		return NULL;
	}
	if (!(dst = malloc(size + 1)))
		return NULL;
	if (src)
	{
		mem_size = ft_memsize(src);
		ft_memcpy(dst, src, mem_size);
		ft_bzero(&dst[mem_size], size - mem_size);
		ft_memdel(&src);
	}
	return dst;
}
