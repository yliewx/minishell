/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:51:48 by yliew             #+#    #+#             */
/*   Updated: 2023/09/16 17:16:10 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
/*
static void	test_run(void *s1, int c, size_t n, int test)
{
	void	*res1 = ft_memchr(s1, c, n);
	void	*res2 = memchr(strdup((char *)s1), c, n);

	if (strcmp(res1, res2) == 0)
		printf("Test %i Success\n", test);
	else
		printf("Test %i Failed; Expected: %s\n", test, (char *)res2);
}

int	main(void)
{
	char	str1[] = "hello world";
	char	str2[6] = {0, 1, 2, 3, 4, 5};
	char	str3[6] = {0, 1, 2, 3, 4, 5};
	char	str4[6] = {0, 1, 2, 3, 4, 5};
	int	tab1[7] = {-49, 49, 1, -1, 0, -2, 2};

	test_run(str1, 'w', 8, 1);
	test_run(str2, 0, 1, 2);
	test_run(str3, 2, 3, 3);
	test_run(str4, 2 + 256, 3, 4);
	test_run(tab1, -1, 7, 5);
	return (0);
}
*/
