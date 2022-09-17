#include "lib_io.h"
#include <stdbool.h>

char *readline(const int fd)
{
	return get_next_line(fd, false);
}

char *free_readline_cache()
{
	return get_next_line(0, true);
}
