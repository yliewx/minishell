/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:19:44 by yliew             #+#    #+#             */
/*   Updated: 2023/09/12 17:59:11 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*s;
	size_t			i;

	dst = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	if (!dst && !s)
		return (NULL);
	while (i < n)
	{
		dst[i] = s[i];
		i++;
	}
	return (dst);
}
/*
static void	test_print(void *dest1, void *dest2, const void *src, size_t n)
{
	printf("Src:     %s\n", (char *)src);
	ft_memcpy(dest1, src, n);
	printf("	(ft_memcpy success)\n");
	memcpy(dest2, src, n);
	printf("	(memcpy success)\n");
	if (memcmp(dest1, dest2, n) == 0)
		printf("Success: %s\n", (char *)dest2);
	else
		printf("Failed\nAfter ft_memcpy: %s\nAfter memcpy:    %s\n",
			(char *)dest1, (char *)dest2);
}

int	main(void)
{
	const char	src[50] = "Lorem ipsum dolor sit amet";
	char	dest1[30];
	char	dest2[30];

	test_print(dest1, dest2, src, ft_strlen(src) + 1);
	test_print((void*)0, (void*)0, "segfaulter tu dois", 17);
	return (0);
}
*/
