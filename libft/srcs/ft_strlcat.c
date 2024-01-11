/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:18:06 by yliew             #+#    #+#             */
/*   Updated: 2023/09/27 16:19:15 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	d;
	size_t	e;

	if (dstsize <= ft_strlen(dest))
		return (dstsize + ft_strlen(src));
	d = ft_strlen(dest);
	e = 0;
	while (src[e] != '\0' && d + 1 < dstsize)
	{
		dest[d] = src[e];
		d++;
		e++;
	}
	dest[d] = '\0';
	return (ft_strlen(dest) + ft_strlen(src + e));
}*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	d;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	d = dst_len;
	i = 0;
	if (!src)
		return (src_len);
	else if (size <= dst_len)
		return (src_len + size);
	while (i < (size - dst_len - 1) && src[i])
	{
		dst[d + i] = src[i];
		i++;
	}
	dst[d + i] = '\0';
	return (dst_len + src_len);
}
/*
static void	test_print(size_t res, char *dst, size_t size, int ver)
{
	char	*msg;

	if (ver == 1)
		msg = "After ft_strlcat: ";
	else
		msg = "After strlcat:    ";
	if (res >= size)
		printf("%s%s\n(%lu: exceeded)\n", msg, dst, res);
	else
		printf("%s%s\n(%lu)\n", msg, dst, res);
}

int	main(void)
{
	char	dst1[60] = "Lorem";
	char	dst2[60] = "Lorem";
	char	src[] = " ipsum dolor sit amet, consectetur adipiscing elit.";
	char	*dst3 = malloc(sizeof(char) * 15);
	char	*dst4 = malloc(sizeof(char) * 15);
	size_t	size1 = 30;
	size_t	size2 = 15;
	size_t	size3 = 0;

	printf("Dest: %s\n", dst1);
	test_print(ft_strlcat(dst1, src, size1), dst1, size1, 1);
	test_print(strlcat(dst2, src, size1), dst2, size1, 2);
	test_print(ft_strlcat(dst3, "", size2), dst3, size2, 1);
	test_print(strlcat(dst4, "", size2), dst4, size2, 2);
	test_print(ft_strlcat(dst3, src, size3), dst3, size3, 1);
	test_print(strlcat(dst4, src, size3), dst4, size3, 2);
	return (0);
}*/
