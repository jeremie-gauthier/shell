#include <stddef.h>

size_t ft_strlen(const char *const restrict s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return len;
}
