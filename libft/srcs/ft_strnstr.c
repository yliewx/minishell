/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:00:28 by yliew             #+#    #+#             */
/*   Updated: 2023/09/07 11:44:16 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	char	*str;
	char	*sub;
	size_t	i;
	size_t	j;

	str = (char *)haystack;
	sub = (char *)needle;
	i = 0;
	if (!sub[0])
		return (str);
	while (str[i] && i < n)
	{
		j = 0;
		while (sub[j] && i + j < n)
		{
			if (str[i + j] != sub[j])
				break ;
			j++;
		}
		if (!sub[j])
			return (&str[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	str[] = "Hello World!";
	
	printf("1st occurrence of World: %s\n", ft_strnstr(str, "World", 10));
	printf("1st occurrence of World: %s\n", strnstr(str, "World", 10));
	return (0);
}
*/
