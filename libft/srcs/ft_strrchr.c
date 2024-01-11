/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:47:17 by yliew             #+#    #+#             */
/*   Updated: 2023/09/12 18:42:32 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = ft_strlen(str) - 1;
	if ((unsigned char)c == 0)
		return (str + i + 1);
	while (i >= 0)
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return (&str[i]);
		i--;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	str1[] = "hello world";
	char	str2[] = "tripouille";

	printf("After ft_strrchr: %s\n", ft_strrchr(str1, 'l'));
	printf("After strrchr:    %s\n", strrchr(str1, 'l'));
	printf("After ft_strrchr: %s\n", ft_strrchr(str2, 't' + 256));
	printf("After strrchr:    %s\n", strrchr(str2, 't' + 256));
	printf("After ft_strrchr: %s\n", ft_strrchr(str2, 0));
	printf("After strrchr:    %s\n", strrchr(str2, 0));
	printf("After ft_strrchr: %s\n", ft_strrchr("", 0));
	printf("After strrchr:    %s\n", strrchr("", 0));
	printf("After ft_strrchr: %s\n", ft_strrchr("teste", 1024));
	printf("After strrchr:    %s\n", strrchr("teste", 1024));
	return (0);
}
*/
