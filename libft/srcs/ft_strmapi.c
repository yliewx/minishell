/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:34:03 by yliew             #+#    #+#             */
/*   Updated: 2023/09/08 12:06:20 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dst;
	unsigned int	len;
	unsigned int	i;

	len = ft_strlen(s);
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = f(i, s[i]);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
/*
static char	test_shift(unsigned int i, char c)
{
	return (c + i);
}

int	main(void)
{
	char	str1[] = "012345678";
	char	str2[] = "HELLOWORLD";
	char	*res;

	res = ft_strmapi(str1, test_shift);
	printf("Original: %s\nResult:   %s\n", str1, res);
	res = ft_strmapi(str2, test_shift);
	printf("Original: %s\nResult:   %s\n", str2, res);
	return (0);
}
*/
