#include <stddef.h>

size_t ft_arr_len(char **arr)
{
	size_t len = 0;
	while (arr[len])
		len++;
	return len;
}
