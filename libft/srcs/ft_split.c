/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:05:28 by yliew             #+#    #+#             */
/*   Updated: 2023/09/21 18:34:17 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	new_strlen(char *s, char c, size_t pos)
{
	size_t	i;

	i = 0;
	while (s[pos] && s[pos] != c)
	{
		i++;
		pos++;
	}
	return (i);
}

static char	**backtrack_free(char **arr, int j)
{
	while (j >= 0)
	{
		free(arr[j]);
		j--;
	}
	free(arr);
	return (NULL);
}

static char	*store_str(char *str, char c, size_t pos)
{
	size_t	i;
	size_t	new_len;
	char	*new_str;

	i = 0;
	new_len = new_strlen(str, c, pos);
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

static char	**split_str(char **arr, char *str, char c, size_t str_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] && j < str_count)
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			arr[j] = store_str(str, c, i);
			if (arr[j] == NULL)
				return (backtrack_free(arr, j));
			j++;
		}
		while (str[i] && str[i] != c)
			i++;
	}
	arr[j] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
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
		if (str[i] != c && (str[i + 1] == c || !(str[i + 1])))
			str_count++;
		i++;
	}
	arr = malloc((str_count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr = split_str(arr, str, c, str_count);
	return (arr);
}
/*
static void	test_print(char *str, char **split)
{
	int	i = 0;

	printf("Original string:\n%s\nAfter split:\n", str);

	while (split[i])
	{
                printf("%s\n", split[i]);
		i++;
	}
}

int	main(void)
{
	char	*str1 = strdup("hello, world,@world/wor,lds");
	char	**res1 = ft_split(str1, ',');
	char	*str2 = strdup("--1-2--3---4----5-----42");
	char	**res2 = ft_split(str2, '-');
	char	*str3 = strdup("hello!");
	char	**res3 = ft_split(str3, ' ');

	test_print(str1, res1);
	test_print(str2, res2);
	test_print(str3, res3);
	return (0);
}
*/
