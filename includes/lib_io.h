#ifndef LIB_IO_H
#define LIB_IO_H

#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>

#define GNL_BUFFER_SIZE 256

typedef struct s_gnl
{
	char *cache;
	size_t bytes_alloc;
	size_t len;
} t_gnl;

bool can_readf(const int fd);
char *get_next_line(const int fd, const bool release_memory);
char *readline(const int fd);
char *free_readline_cache();

#endif
