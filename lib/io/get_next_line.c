#include "lib_io.h"
#include "lib_mem.h"
#include "lib_str.h"
#include <stdio.h>
#include <stdlib.h>

static char *fill_line_from_cache(char *const restrict cache, char **line)
{
	char *nl;

	if ((nl = ft_strchr(cache, '\n')))
	{
		*line = ft_strndup(cache, &nl[1] - cache);
		if (nl[1] == '\0')
			return NULL;
		return ft_strdup(&nl[1]);
	}
	*line = ft_strdup(cache);
	return NULL;
}

static int read_fd(const int fd, char **const cache)
{
	char buf[BUFFER_SIZE + 1];
	char *cache_ptr;
	int ret;

	if (!*cache || !ft_strchr(*cache, '\n'))
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		if (ret == 0)
			return 0;
		cache_ptr = *cache;
		if (!(*cache = ft_strjoin(*cache, buf)))
			return (-1);
		ft_strdel(&cache_ptr);
	}
	while (!ft_strchr(buf, '\n') && ret == BUFFER_SIZE)
	{
		// printf("cache [%s]\n", *cache);
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		if (ret == 0)
			return 0;
		cache_ptr = *cache;
		if (!(*cache = ft_strjoin(*cache, buf)))
			return (-1);
		ft_strdel(&cache_ptr);
		ft_bzero(buf, ret); // for clean log during debug, but not necessary
	}
	return 0;
}

char *get_next_line(const int fd)
{
	static char *cache = NULL;
	char *cache_ptr;
	char *line;

	if (fd < 0 || !can_readf(fd))
		return NULL;
	if (read_fd(fd, &cache) < 0)
		return NULL;
	if (!cache)
		return NULL;
	cache_ptr = cache;
	// printf("cache before [%s]\n", cache);
	cache = fill_line_from_cache(cache, &line);
	// printf("cache after [%s]\n", cache);
	ft_strdel(&cache_ptr);
	return line;
}
