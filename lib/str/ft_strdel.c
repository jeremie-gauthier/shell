#include <stddef.h>
#include <stdlib.h>

void ft_strdel(char *restrict *const restrict as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
}
