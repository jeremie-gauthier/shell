/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jergauth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:38:37 by jergauth          #+#    #+#             */
/*   Updated: 2019/01/31 15:42:38 by jergauth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_mem.h"
#include "lib_str.h"
#include <stdbool.h>
#include <stdlib.h>

static char *ft_strcdup(const char *str, const char limit)
{
	size_t len = 0;
	while (str[len] && str[len] != limit)
		len++;
	return ft_strndup(str, len);
}

static size_t count_words(char const *str, char c)
{
	size_t words;
	bool in_word;

	words = 0;
	in_word = false;
	while (*str)
	{
		if (*str != c && in_word == 0)
		{
			in_word = true;
			words++;
		}
		else if (*str == c)
			in_word = false;
		str++;
	}
	return words;
}

static void ft_strsplit_free(char **arr, size_t size)
{
	size_t i = 0;
	while (i < size)
	{
		ft_strdel(&arr[i]);
		i++;
	}
	ft_memdel((void **)arr);
}

char **ft_strsplit(char const *str, char c)
{
	if (!str)
		return NULL;

	char **arr;
	const size_t arr_len = count_words(str, c);
	if (!(arr = malloc(sizeof(*arr) * (arr_len + 1))))
		return (NULL);

	size_t i = 0;
	while (i < arr_len)
	{
		while (*str == c)
			str++;
		if (!(arr[i] = ft_strcdup(str, c)))
		{
			ft_strsplit_free((void *)arr, i);
			return NULL;
		}
		while (*str && *str != c)
			str++;
		i++;
	}
	arr[i] = NULL;
	return arr;
}
