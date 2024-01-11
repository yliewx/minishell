/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:49:52 by yliew             #+#    #+#             */
/*   Updated: 2023/09/07 11:45:18 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (str);
}
/*
int	main(void)
{
	char	str[] = "hello world!";

	printf("%s\n", str);
	printf("ft_memset: %s\n", (char *)(ft_memset(str, '!', 4)));
	printf("memset: %s\n", (char *)(memset(str, '!', 4)));
	printf("%s\n", str);
	printf("ft_memset: %s\n", (char *)(ft_memset(str, '-', 8)));
	printf("memset: %s\n", (char *)(memset(str, '-', 8)));
	return (0);
}
*/
