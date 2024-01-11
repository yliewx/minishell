/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:30:20 by yliew             #+#    #+#             */
/*   Updated: 2023/09/13 13:43:33 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		sub = malloc(1 * sizeof(char));
	else if (start + len <= s_len)
		sub = malloc((len + 1) * sizeof(char));
	else
		sub = malloc((s_len - start + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while ((start + i) < s_len && i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
/*
static void	test_check(void *str, void *res, void *expected)
{
	size_t	res_size = malloc_usable_size(res);	
	size_t	exp_size = malloc_usable_size(expected);

	printf("String:  %s\n", (char *)str);
	if (res_size == exp_size)
		printf("Success: %s\nMalloc size: %lu [Expected: %lu]\n\n",
			(char *)res, res_size, exp_size);
	else
		printf("FAILED:  %s\nMalloc size: %lu [Expected: %lu]\n\n",
			(char *)res, res_size, exp_size);
	free(res);
	free(expected);
}

int	main(void)
{
	char	str1[] = "Lorem ipsum dolor sit amet";
	char	str2[] = "01234";
	char	str3[] = "tripouille";
	char	*str4 = strdup("1");
	char	*str5 = strdup("0123456789");
	size_t	size = 10;

	printf("%lu\n", malloc_usable_size(malloc(1)));
	test_check(str2, ft_substr(str2, 10, size), malloc(strlen("")));
	test_check(str3, ft_substr(str3, 0, 42000), malloc(strlen(str3) + 1));
	test_check(str3, ft_substr(str3, 100, 1), malloc(1));
	test_check(str4, ft_substr(str4, 42, 42000000), malloc(1));
	test_check(str5, ft_substr(str5, 9, 10), malloc(2));
	printf("String:    %s\nSubstring: %s\n", str1, ft_substr(str1, 6, 4));
	printf("String:    %s\nSubstring: %s\n", str1, ft_substr(str1, 0, 10));
	printf("String:    %s\nSubstring: %s\n", str1, ft_substr(str1, 7, 10));
	return (0);
}
*/
