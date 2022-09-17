#include <stddef.h>

void *ft_memcpy(void *dst, const void *const src, size_t n)
{
	char *dst_ptr;
	char const *src_ptr;

	if (!dst && !src)
		return NULL;
	dst_ptr = (char *)dst;
	src_ptr = (const char *)src;
	while (n--)
		*dst_ptr++ = *src_ptr++;
	return dst;
}
