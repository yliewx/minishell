/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:25:04 by yliew             #+#    #+#             */
/*   Updated: 2023/09/12 17:28:05 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*str1;
	char	*str2;
	size_t	i;

	str1 = (char *)s1;
	str2 = (char *)s2;
	i = 0;
	if (n <= 0)
		return (0);
	if (!str1 || !str2)
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	while (i < n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i]
				- (unsigned char)str2[i]);
		i++;
	}
	return (0);
}
/*
static void	test_run(char *test1, char *test2, size_t n, int i)
{
	printf("Test %i:\nft_memcmp: %d\nmemcmp:    %d\n",
		i + 1, ft_memcmp(test1, test2, n), memcmp(test1, test2, n));
}

int	main(void)
{
	char	*test1[] = {"hello WORLD", "HELLO world", "-31", "+31",
			"atoms\0\0\0\0", "\xff\0\0\xaa\0\xde\xffMACOSX\xff"};
	char	*test2[] = {"hello world", "HELLO WORLD", "8", "8",
			"atoms\0abc", "\xff\0\0\xaa\0\xde\x00MBS"};
	int	i = 0;

	while (i < 5)
	{
		test_run(test1[i], test2[i], 4, i);
		if (i == 4)
			test_run(test1[i], test2[i], 8, i);
		else if (i == 5)	
			test_run(test1[i], test2[i], 9, i);
		i++;
	}
	return (0);
}
*/
