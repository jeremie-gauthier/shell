#include "lib_str.h"
#include <stdlib.h>

char *ft_arr_join(char **arr)
{
	size_t length = 0;
	size_t i = 0;

	while (arr[i])
	{
		length += ft_strlen(arr[i]);
		i++;
	}

	size_t last_idx = 0;
	char *str = ft_strnew(length);
	i = 0;
	while (arr[i])
	{
		ft_strcpy(&str[last_idx], arr[i]);
		last_idx += ft_strlen(arr[i]);
		i++;
	}
	str[length] = '\0';
	return str;
}
