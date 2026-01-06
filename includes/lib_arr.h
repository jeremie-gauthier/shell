#ifndef LIB_ARR_H
#define LIB_ARR_H

#include <stddef.h>

void ft_print_arr(const char *const *const arr);
void ft_arr_free(char **arr, size_t size);
size_t ft_arr_len(const char *const *const arr);
char **ft_arr_append(char **arr, const char *const item);
char **ft_arr_new(size_t size);
char *ft_arr_join(char **arr);

#endif
