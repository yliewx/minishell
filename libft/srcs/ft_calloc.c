/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:23:35 by yliew             #+#    #+#             */
/*   Updated: 2023/09/12 16:21:08 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*dest;

	dest = malloc(nmemb * size);
	if (!dest)
		return (NULL);
	ft_bzero(dest, nmemb * size);
	return (dest);
}
/*
static void	test_print(char *dest1, char *dest2, int test)
{
	if (strcmp(dest1, dest2) == 0)
		printf("Test %i: Success\n", test);
	else
		printf("Test %i: Failed\n", test);
}

int	main(void)
{
	test_print(ft_calloc(5, sizeof(char)), calloc(5, sizeof(char)), 1);
	test_print(ft_calloc(0, 0), calloc(0, 0), 2);
	return (0);
}
*/
