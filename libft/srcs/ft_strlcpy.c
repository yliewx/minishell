/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:00:40 by yliew             #+#    #+#             */
/*   Updated: 2023/10/06 12:45:44 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
static void     test_print(size_t res, char *dst, int ver)
{
	char	*msg;

	if (ver == 1)
		msg = "After ft_strlcpy: ";
	else
		msg = "After strlcpy:    ";
	printf("%s%s\n(%lu)\n", msg, dst, res);
}

int     main(void)
{
        char    src1[] = "Hello World!!!";
	char	src2[] = "lorem ipsum dolor sit amet";
        char    dst1[50] = "test1";
	char	dst2[50] = "test1";
	char	*dst3 = malloc(sizeof(char) * 15);
	char	*dst4 = malloc(sizeof(char) * 15);

        printf("Before ft_strlcpy: %s\n", dst1);
	test_print(ft_strlcpy(dst1, src1, 12), dst1, 1);
	test_print(strlcpy(dst2, src1, 12), dst2, 2);
	test_print(ft_strlcpy(dst3, src2, 0), dst3, 1);
	test_print(strlcpy(dst4, src2, 0), dst4, 2);
	return (0);
}
*/
