/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:47:32 by yliew             #+#    #+#             */
/*   Updated: 2024/01/17 16:47:40 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static size_t	new_strlen(char *s, size_t pos)
{
	size_t	i;

	i = 0;
	while (s[pos] && !is_whitespace(s[pos]))
	{
		i++;
		pos++;
	}
	return (i);
}

static char	*store_str(char *str, size_t pos)
{
	size_t	i;
	size_t	new_len;
	char	*new_str;

	i = 0;
	new_len = new_strlen(str, pos);
	new_str = malloc((new_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (i < new_len && str[pos])
	{
		new_str[i] = str[pos];
		i++;
		pos++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static char	**split_str(char **arr, char *str, size_t str_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] && j < str_count)
	{
		while (is_whitespace(str[i]))
			i++;
		if (str[i])
		{
			arr[j] = store_str(str, i);
			j++;
		}
		while (str[i] && !is_whitespace(str[i]))
			i++;
	}
	arr[j] = NULL;
	return (arr);
}

/* Function to split a string by whitespaces
- Does not account for quotes */
char	**ft_split_whitespace(char const *s)
{
	char	**arr;
	char	*str;
	size_t	str_count;
	size_t	i;

	str = (char *)s;
	i = 0;
	str_count = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i])
			&& (is_whitespace(str[i + 1]) || !(str[i + 1])))
			str_count++;
		i++;
	}
	arr = malloc((str_count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr = split_str(arr, str, str_count);
	return (arr);
}
