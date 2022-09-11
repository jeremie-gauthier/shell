#include "lib_mem.h"
#include "lib_str.h"

void ft_strclr(char *s)
{
	if (s)
		ft_bzero(s, ft_strlen(s));
}
