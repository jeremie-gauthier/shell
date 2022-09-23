#ifndef LIB_STR_H
#define LIB_STR_H

#include <stddef.h>

#define SAME_STR 0

char *ft_strchr(const char *str, int c);
char *ft_strstr(const char *haystack, const char *needle);
int ft_strcmp(const char *s1, const char *s2);
int ft_strncmp(const char *s1, const char *s2, size_t n);
size_t ft_strlen(const char *s);
char *ft_strnew(const size_t size);
void ft_strdel(char **const restrict as);
char *ft_strdup(const char *const restrict s);
char *ft_strndup(const char *const restrict src, size_t n);
char *ft_strcpy(char *const dst, const char *restrict src);
char *ft_strncpy(char *const dest, const char *restrict src, size_t n);
char *ft_strjoin(const char *const restrict s1, const char *const restrict s2, const char *const restrict junction);
void ft_strclr(char *s);
char **ft_strsplit(char const *str, char c);
int ft_strisnum(const char *const str);

#endif
