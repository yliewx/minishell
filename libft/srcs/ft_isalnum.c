/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:28:05 by yliew             #+#    #+#             */
/*   Updated: 2023/09/06 18:30:38 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
/*
int	main(void)
{
	char	*test[6] = {"a", "A", "0", "7", "@", ""};
	int	i = 0;

	while (i < 6)
	{
		printf("%s: %i\n", test[i], ft_isalnum((int)(*test[i])));
		i++;
	}
	return (0);
}
*/
