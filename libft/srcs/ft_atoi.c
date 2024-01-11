/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:42:44 by yliew             #+#    #+#             */
/*   Updated: 2023/09/11 10:59:13 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}
/*
int	main(void)
{
	printf("ft_atoi: %i\natoi:    %i\n", ft_atoi("0"), atoi("0"));
	printf("ft_atoi: %i\natoi:    %i\n",
		ft_atoi("-2147483648"), atoi("-2147483648"));
	printf("ft_atoi: %i\natoi:    %i\n",
		ft_atoi("2147483647"), atoi("2147483647"));
	printf("ft_atoi: %i\natoi:    %i\n", ft_atoi("1428:5"), atoi("1428:5"));
	printf("ft_atoi: %i\natoi:    %i\n", ft_atoi("+2390"), atoi("+2390"));
	printf("ft_atoi: %i\natoi:    %i\n", ft_atoi("00042"), atoi("00042"));
	printf("ft_atoi: %i\natoi:    %i\n", ft_atoi("++99+9"), atoi("++99+9"));
	printf("ft_atoi: %i\natoi:    %i\n",
		ft_atoi("--92830"), atoi("--92830"));
	printf("ft_atoi: %i\natoi:    %i\n",
		ft_atoi("-2048def0"), atoi("-2048def0"));
	printf("ft_atoi: %i\natoi:    %i\n",
		ft_atoi("   34527 9"), atoi("   34527 9"));
	printf("ft_atoi: %i\natoi:    %i\n",
		ft_atoi("\t1234"), atoi("\t1234"));
	printf("ft_atoi: %i\natoi:    %i\n",
		ft_atoi("\n\n243u2"), atoi("\n\n243u2"));
	printf("ft_atoi: %i\natoi:    %i\n",
		ft_atoi("\t\n\r\v\fd120 \n"), atoi("\t\n\r\v\fd120 \n"));
	return (0);
}
*/
