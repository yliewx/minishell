/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:18:59 by yliew             #+#    #+#             */
/*   Updated: 2023/09/06 11:52:06 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}
/*
int	main(void)
{
	char	str[] = "hello world!";
	int	i = 0;
	int	len = ft_strlen(str);

	printf("%s\n", str);
	ft_bzero(str, 3);
	while (i < len)
	{
		printf("%c", str[i]);
		i++;
	}
	return (0);
}
*/
