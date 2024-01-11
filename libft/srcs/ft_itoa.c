/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:06:58 by yliew             #+#    #+#             */
/*   Updated: 2023/09/08 11:31:56 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrlen(long n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count++);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	len;
	long	nbr;

	nbr = n;
	len = ft_nbrlen(nbr);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	if (nbr == 0)
		str[len] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (nbr != 0)
	{
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
		len--;
	}
	return (str);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(INT_MIN));
	printf("%s\n", ft_itoa(INT_MAX));
	printf("%s\n", ft_itoa(100));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(9));
	printf("%s\n", ft_itoa(-198279));
	printf("%s\n", ft_itoa(-92084390));
	return (0);
}
*/
