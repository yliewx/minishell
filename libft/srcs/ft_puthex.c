/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:58:11 by yliew             #+#    #+#             */
/*   Updated: 2023/09/28 16:41:55 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_nbrlen(size_t n)
{
	int	count;

	count = 0;
	while (n != 0)
	{
		n /= 16;
		count++;
	}
	return (count++);
}

void	ft_putptr(size_t p, const char *base, int *len)
{
	if (!p)
	{
		ft_putstr("(nil)", len);
		return ;
	}
	ft_putstr("0x", len);
	ft_puthex(p, base, len);
}

void	ft_puthex(size_t n, const char *base, int *len)
{
	char	*result;
	int		i;

	if (n == 0)
	{
		ft_putchar('0', len);
		return ;
	}
	i = ft_nbrlen(n);
	result = malloc((i + 1) * sizeof(char));
	if (!result)
		return ;
	result[i] = '\0';
	i--;
	while (n != 0)
	{
		result[i] = base[n % 16];
		n /= 16;
		i--;
	}
	ft_putstr(result, len);
	free(result);
}
