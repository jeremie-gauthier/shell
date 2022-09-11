#include "lib_io.h"
#include "lib_mem.h"
#include "lib_str.h"
#include <stdbool.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

static char *get_line_from_cache(t_gnl *const restrict gnl)
{
	char *nl;
	char *line;
	size_t line_size;

	if ((nl = ft_strchr(gnl->cache, '\n')))
	{
		line_size = &nl[1] - gnl->cache;
		line = ft_strndup(gnl->cache, line_size);
		if (nl[1] == '\0')
		{
			gnl->cache[0] = '\0';
			gnl->len = 0;
		}
		else
		{
			ft_strcpy(gnl->cache, &nl[1]);
			gnl->len -= line_size;
		}
		return line;
	}
	line = ft_strdup(gnl->cache);
	gnl->cache[0] = '\0';
	gnl->len = 0;
	return line;
}

static void increase_cache_size(t_gnl *const restrict gnl)
{
	size_t new_size;

	new_size = gnl->bytes_alloc + GNL_BUFFER_SIZE;
	if (!(gnl->cache = ft_realloc(gnl->cache, new_size)))
		return;
	gnl->bytes_alloc = new_size;
}

static bool should_realloc(t_gnl *const restrict gnl)
{
	long int diff;

	diff = gnl->bytes_alloc - gnl->len;
	if (diff < GNL_BUFFER_SIZE)
		return true;
	return false;
}

static int read_fd(const int fd, t_gnl *const restrict gnl)
{
	int ret;

	if (should_realloc(gnl))
		increase_cache_size(gnl);
	if (!gnl->cache || !ft_strchr(gnl->cache, '\n'))
	{
		ret = read(fd, &gnl->cache[gnl->len], GNL_BUFFER_SIZE);
		gnl->len += ret;
		gnl->cache[gnl->len] = '\0';
		if (ret == 0)
			return 0;
	}
	while (!ft_strchr(&gnl->cache[gnl->len - GNL_BUFFER_SIZE], '\n') && ret == GNL_BUFFER_SIZE)
	{
		if (should_realloc(gnl))
			increase_cache_size(gnl);
		ret = read(fd, &gnl->cache[gnl->len], GNL_BUFFER_SIZE);
		gnl->len += ret;
		gnl->cache[gnl->len] = '\0';
		if (ret == 0)
			return 0;
	}
	return 0;
}

char *get_next_line(const int fd, const bool release_memory)
{
	static t_gnl gnl = {.bytes_alloc = 0, .cache = NULL, .len = 0};

	if (release_memory)
	{
		ft_strdel(&gnl.cache);
		gnl.bytes_alloc = 0;
		gnl.len = 0;
		return NULL;
	}
	if (fd < 0 || !can_readf(fd))
		return NULL;
	if (read_fd(fd, &gnl) < 0)
		return NULL;
	if (gnl.len == 0)
		return NULL;
	return get_line_from_cache(&gnl);
}
