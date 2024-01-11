/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:48:07 by yliew             #+#    #+#             */
/*   Updated: 2023/09/11 17:40:25 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	d;
	size_t	i;

	d = ft_strlen(s1);
	dst = malloc((d + ft_strlen(s2) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		dst[d + i] = s2[i];
		i++;
	}
	dst[d + i] = '\0';
	return (dst);
}
/*
static void	print_test(char const *s1, char const *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	printf("S1: %s\nS2: %s\nAfter ft_strjoin: %s\n", s1, s2, result);
	free(result);
}

int	main(void)
{
	print_test("Hello", " World");
	print_test("", "");
	print_test("Lorem", "");
	print_test("", "ipsum");
	return (0);
}
*/
