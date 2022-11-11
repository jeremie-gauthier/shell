#include <stddef.h>
#include <stdlib.h>

void ft_strdel(char **const as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
}
