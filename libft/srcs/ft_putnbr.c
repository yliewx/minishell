/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:51:02 by yliew             #+#    #+#             */
/*   Updated: 2023/09/22 11:37:38 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putnbr(int n, int *len)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*len) += 11;
	}
	else if (n < 0)
	{
		ft_putchar('-', len);
		ft_putnbr(n * -1, len);
	}
	else if (n >= 10)
	{
		ft_putnbr(n / 10, len);
		ft_putnbr(n % 10, len);
	}
	else
		ft_putchar(n + '0', len);
}

void	ft_putunsigned(unsigned int n, int *len)
{
	if (n >= 10)
	{
		ft_putunsigned(n / 10, len);
		ft_putunsigned(n % 10, len);
	}
	else
		ft_putchar(n + '0', len);
}
