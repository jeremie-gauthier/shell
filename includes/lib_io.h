#ifndef LIB_IO_H
#define LIB_IO_H

#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>

// typedef struct s_file
// {
// 	struct s_file *next;
// 	char *str;
// 	int fd;
// } t_file;

// int get_next_line(const int fd, char **line);
char *get_next_line(const int fd);
bool can_readf(const int fd);

#endif
