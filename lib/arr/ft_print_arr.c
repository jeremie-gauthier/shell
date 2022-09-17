#include <stddef.h>
#include <stdio.h>

void ft_print_arr(const char *const *const arr)
{
	size_t i = 0;

	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
	fflush(stdout);
}
