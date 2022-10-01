#include <stddef.h>

size_t ft_arr_len(const char *const *const arr)
{
	size_t len = 0;
	while (arr[len])
		len++;
	return len;
}
