#include "lib_io.h"
#include "lib_mem.h"
#include "lib_str.h"
#include <stdio.h>
#include <stdlib.h>

static void fill_line_from_cache(t_gnl *const restrict gnl, char **line)
{
	char *nl;
	size_t line_size;

	if ((nl = ft_strchr(gnl->cache, '\n')))
	{
		line_size = &nl[1] - gnl->cache;
		*line = ft_strndup(gnl->cache, line_size);
		if (nl[1] == '\0')
		{
			ft_bzero(gnl->cache, gnl->bytes_alloc);
			gnl->len = 0;
			return;
		}
		ft_strcpy(gnl->cache, &nl[1]);
		ft_bzero(&gnl->cache[line_size], gnl->bytes_alloc - gnl->len);
		// printf("in alloc %zu  len %zu  cache [%s] line_size %zu\n", gnl->bytes_alloc, gnl->len, gnl->cache, line_size);
		gnl->len -= line_size;
		return;
	}
	*line = ft_strdup(gnl->cache);
	ft_bzero(gnl->cache, gnl->bytes_alloc);
	gnl->len = 0;
	return;
}

static void increase_cache_size(t_gnl *const restrict gnl)
{
	size_t new_size;

	new_size = gnl->bytes_alloc + BUFFER_SIZE;
	if (!(gnl->cache = ft_realloc(gnl->cache, new_size)))
		return;
	gnl->bytes_alloc = new_size;
}

static bool should_realloc(t_gnl *const restrict gnl)
{
	long int diff;

	diff = gnl->bytes_alloc - gnl->len;
	if (diff < BUFFER_SIZE)
		return true;
	return false;
}

static int read_fd(const int fd, t_gnl *const restrict gnl)
{
	// char *cache_ptr;
	int ret;

	if (should_realloc(gnl))
		increase_cache_size(gnl);
	if (!gnl->cache || !ft_strchr(gnl->cache, '\n'))
	{
		ret = read(fd, &gnl->cache[gnl->len], BUFFER_SIZE);
		gnl->len += ret;
		gnl->cache[gnl->len] = '\0';
		if (ret == 0)
			return 0;
		// cache_ptr = *cache;
		// if (!(*cache = ft_strjoin(*cache, buf)))
		// 	return (-1);
		// ft_strdel(&cache_ptr);
	}
	// printf("%s\n", &gnl->cache[gnl->len - BUFFER_SIZE]);
	while (!ft_strchr(&gnl->cache[gnl->len - BUFFER_SIZE], '\n') && ret == BUFFER_SIZE)
	{
		// printf("%zu %s\n", gnl->len - BUFFER_SIZE, &gnl->cache[gnl->len - BUFFER_SIZE]);
		if (should_realloc(gnl))
			increase_cache_size(gnl);
		ret = read(fd, &gnl->cache[gnl->len], BUFFER_SIZE);
		gnl->len += ret;
		gnl->cache[gnl->len] = '\0';
		if (ret == 0)
			return 0;
		// cache_ptr = *cache;
		// if (!(*cache = ft_strjoin(*cache, buf)))
		// 	return (-1);
		// ft_strdel(&cache_ptr);
	}
	return 0;
}

char *get_next_line(const int fd)
{
	static t_gnl gnl = {.bytes_alloc = 0, .cache = NULL, .len = 0};
	// char *cache_ptr;
	char *line;

	// printf("start alloc %zu  len %zu\n", gnl.bytes_alloc, gnl.len);
	if (fd < 0 || !can_readf(fd))
		return NULL;
	if (read_fd(fd, &gnl) < 0)
		return NULL;
	if (gnl.len == 0)
		return NULL;
	// cache_ptr = cache;
	// printf("bf alloc %zu  len %zu  cache [%s]\n", gnl.bytes_alloc, gnl.len, gnl.cache);
	fill_line_from_cache(&gnl, &line);
	// printf("af alloc %zu  len %zu  cache [%s]\n", gnl.bytes_alloc, gnl.len, gnl.cache);
	// ft_strdel(&cache_ptr);
	return line;
}
