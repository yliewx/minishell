/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:08:04 by yliew             #+#    #+#             */
/*   Updated: 2023/09/08 18:44:46 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
/*
static void	test_revcase(unsigned int i, char *s)
{
	if (i > 100)
		return ;
	if (*s >= 'a' && *s <= 'z')
		*s -= 32;
	else if (*s >= 'A' && *s <= 'Z')
		*s += 32;
}

int	main(void)
{
	char	str1[] = "HELLOWORLD";
	char	str2[] = "lorem iPsum /f,S.l;'";
	char	str3[] = " a102942Eh";
	char	str4[] = "";
	char	*str5 = malloc(sizeof(char) * 12);

	printf("Original: %s\n", str1);
	ft_striteri(str1, test_revcase);
	printf("Result:   %s\n", str1);
	printf("Original: %s\n", str2);
	ft_striteri(str2, test_revcase);
	printf("Result:   %s\n", str2);
	printf("Original: %s\n", str3);
	ft_striteri(str3, test_revcase);
	printf("Result:   %s\n", str3);
	printf("Original: %s\n", str4);
	ft_striteri(str4, test_revcase);
	printf("Result:   %s\n", str4);
	strcpy(str5, "LoReM iPsUm");
	ft_striteri(str5, test_revcase);
	printf("Original: LoReM iPsUm\nResult:   %s\n", str5);
	return (0);
}
*/
