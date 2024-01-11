/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:37:36 by yliew             #+#    #+#             */
/*   Updated: 2023/09/06 17:48:46 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1[i] || !s2[i])
	{
		if (n <= 0)
			return (0);
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	*test1[] = {"hello WORLD", "HELLO world", "-31", "+31"};
	char	*test2[] = {"hello world", "HELLO WORLD", "8", "8"};
	int	i = 0;

	while (i < 4)
	{
		printf("ft_strncmp: %d.\n", ft_strncmp(test1[i], test2[i], 4));
		printf("ft_strncmp: %d.\n", ft_strncmp(test1[i], test2[i], 10));
		i++;
	}
	i = 0;
	while (i < 4)
	{
		printf("strncmp:    %d.\n", strncmp(test1[i], test2[i], 4));
		printf("strncmp:    %d.\n", strncmp(test1[i], test2[i], 10));
		i++;
	}
	return (0);
}
*/
