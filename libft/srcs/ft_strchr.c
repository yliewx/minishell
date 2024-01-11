/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:19:53 by yliew             #+#    #+#             */
/*   Updated: 2023/09/15 15:36:35 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	if ((unsigned char)c == 0)
		return (&str[i]);
	return (NULL);
}
/*
int	main(void)
{
	char	str1[] = "hello world";
	char	str2[] = "bonjour";
	char	str3[] = "tripouille";

	printf("After ft_strchr: %s\n", ft_strchr(str1, 'l'));
	printf("After    strchr: %s\n", strchr(str1, 'l'));
	printf("After ft_strchr: %s\n", ft_strchr(str2, 's'));
	printf("After    strchr: %s\n", strchr(str2, 's'));
	printf("After ft_strchr: %s\n", ft_strchr(str2, '\0'));
	printf("After    strchr: %s\n", strchr(str2, '\0'));
	printf("After ft_strchr: %s\n", ft_strchr("", '\0'));
	printf("After    strchr: %s\n", strchr("", '\0'));
	printf("After ft_strchr: %s\n", ft_strchr(str3, 't' + 256));
	printf("After    strchr: %s\n", strchr(str3, 't' + 256));
	printf("After ft_strchr: %p\n", ft_strchr("teste", 1024));
	printf("After    strchr: %p\n", strchr("teste", 1024));
        return (0);
}
*/
