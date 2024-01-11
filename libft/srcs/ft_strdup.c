/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:54:29 by yliew             #+#    #+#             */
/*   Updated: 2023/09/06 14:05:15 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*dest;

	dest = malloc(ft_strlen(s) + 1);
	if (!dest)
		return (NULL);
	ft_strcpy(dest, s);
	return (dest);
}
/*
int	main(void)
{
	char	src[] = "Lorem ipsum dolor sit amet";
	char	*dest;

	printf("%s (%p)\n", src, src);
	dest = ft_strdup(src);
	printf("%s (%p)\n", dest, dest);
	return (0);
}
*/
