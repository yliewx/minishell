/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:07:47 by yliew             #+#    #+#             */
/*   Updated: 2023/09/12 18:25:48 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*s;
	size_t			i;

	dst = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!dst && !s)
		return (NULL);
	if (dst > s && dst < (s + n))
	{
		i = n;
		while (i-- > 0)
			dst[i] = s[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			dst[i] = s[i];
			i++;
		}
	}
	return (dst);
}
/*
int	main(void)
{
	char	str1[50] = "0123456789-+[]";
	char	str2[50] = "0123456789-+[]";
	char	str3[50] = "0123456789-+[]";
	char	str4[50] = "lorem ipsum dolor sit amet";
	char	str5[50] = "lorem ipsum dolor sit amet";
	char	str6[50] = "lorem ipsum dolor sit amet";
	char	str7[50] = "lorem ipsum dolor sit amet";
	char	b[0xF0];

	printf("Original string: %s\n", str1);
	ft_memmove(str1 + 2, str1, 10);
	printf("After ft_memmove: %s\n", str1);
	memmove(str2 + 2, str2, 10);
	printf("After memmove:    %s\n", str2);
	memcpy(str3 + 2, str3, 10);
	printf("After memcpy:     %s\n", str3);
	printf("Original string:  %s\n", str4);
	ft_memmove(str4 + 1, "consectetur", 5);
	printf("After ft_memmove: %s\n", str4);
	memmove(str5 + 1, "consectetur", 5);
	printf("After memmove:    %s\n", str5);
	printf("Original string:  %s\n", str6);
	ft_memmove(str6, str6 + 1, 8);
	printf("After ft_memmove: %s\n", str6);
	memmove(str7, str7 + 1, 8);
	printf("After memmove:    %s\n---Checking for segfault---\n", str7);
	ft_memmove(((void*)0), b, 5);
	printf("ft_memmove success\n");
	return (0);
}
*/
