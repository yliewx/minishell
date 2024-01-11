/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:08:22 by yliew             #+#    #+#             */
/*   Updated: 2023/09/08 13:20:05 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(n * -1, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		n += '0';
		write(fd, &n, 1);
	}
}
/*
int	main(void)
{
	ft_putnbr_fd(INT_MIN, 1);
	printf("\n");
	ft_putnbr_fd(INT_MAX, 1);
	printf("\n");
	ft_putnbr_fd(100, 1);
	printf("\n");
	ft_putnbr_fd(0, 1);
	printf("\n");
	ft_putnbr_fd(9, 1);
	printf("\n");
	ft_putnbr_fd(-234980, 2);
	printf("\n");
        return (0);
}
*/
