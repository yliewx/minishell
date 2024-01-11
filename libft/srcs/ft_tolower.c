/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:09:47 by yliew             #+#    #+#             */
/*   Updated: 2023/09/07 15:07:43 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
/*
int	main(void)
{
	char	test[] = "Lorem ipsum dolor sit amet. Sed non risus.";
	int	i = 0;
	int	len = ft_strlen(test);

	while (i < len)
	{
		printf("%c", ft_tolower((int)(test[i])));
		i++;
	}
	return (0);
}
*/
