/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:14:33 by yliew             #+#    #+#             */
/*   Updated: 2023/10/06 12:47:24 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	check_format(const char s1, int *i, va_list arg, int *len)
{
	if (s1 == 'c')
		ft_putchar(va_arg(arg, int), len);
	else if (s1 == 's')
		ft_putstr(va_arg(arg, char *), len);
	else if (s1 == 'd' || s1 == 'i')
		ft_putnbr(va_arg(arg, int), len);
	else if (s1 == 'u')
		ft_putunsigned(va_arg(arg, unsigned int), len);
	else if (s1 == 'X')
		ft_puthex(va_arg(arg, unsigned int), "0123456789ABCDEF", len);
	else if (s1 == 'x')
		ft_puthex(va_arg(arg, unsigned int), "0123456789abcdef", len);
	else if (s1 == 'p')
		ft_putptr(va_arg(arg, size_t), "0123456789abcdef", len);
	else if (s1 == '%')
		ft_putchar('%', len);
	else
		(*i)--;
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		output_len;
	va_list	arg;

	va_start(arg, str);
	i = 0;
	output_len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i])
				check_format(str[i], &i, arg, &output_len);
		}
		else
			ft_putchar(str[i], &output_len);
		i++;
	}
	va_end(arg);
	return (output_len);
}
/*
int	main(void)
{
	char	s1[] = "Lorem ipsum dolor sit amet, consectetur adipiscing";
	char	s2[] = "elit, sed do eiusmod tempor incididunt ut labore et";
	char	s3[] = "dolore magna aliqua. Ut enim ad minim veniam, quis";
	char	s4[] = "nostrud exercitation ullamco laboris nisi ut aliquip";
	char	s5[] = "ex ea commodo consequat.";
	char	*s6 = NULL;

	ft_printf("\nft_printf (string): \n");
	ft_printf("Return value: %i\n",
		ft_printf("%s %s %s %s %s\n%s\n", s1, s2, s3, s4, s5, s6));
	printf("\nOriginal printf (string): \n");
	printf("Return value: %i\n",
		printf("%s %s %s %s %s\n%s\n", s1, s2, s3, s4, s5, s6));
	ft_printf("\nft_printf (mix): \n");
	ft_printf("Return value: %i\n",
		ft_printf("%c%c%c%s%c%%%ctest%c%ctest\n",
		'a', '@', '\t', "&*?=^	!*#:3", '\n', '\v', ' ', '-'));
	printf("\nprintf (mix): \n");
	printf("Return value: %i\n",
		printf("%c%c%c%s%c%%%ctest%c%ctest\n",
		'a', '@', '\t', "&*?=^	!*#:3", '\n', '\v', ' ', '-'));
	ft_printf("\nft_printf (int): \n");
	ft_printf("Return value: %i\n",
		ft_printf("%i %d %i %d %i\n", 0, 1, 42, 999, INT_MIN));
	printf("\nOriginal printf (int): \n");
	printf("Return value: %i\n",
		printf("%i %d %i %d %i\n", 0, 1, 42, 999, INT_MIN));
	ft_printf("\nft_printf (unsigned int): \n");
	ft_printf("Return value: %i\n", ft_printf("%u %u %u %u %u %u\n",
		1, -1, UINT_MAX, 0, 4309, -90));
	printf("\nOriginal printf (unsigned int): \n");
	printf("Return value: %i\n", printf("%u %u %u %u %u %u\n",
		1, -1, UINT_MAX, 0, 4309, -90));
	ft_printf("\nft_printf (hexadecimal): \n");
	ft_printf("Return value: %i\n", ft_printf("%x %x %x %x %X %X %X %%\n",
		1, -1, 0, 100, 2048, INT_MIN, INT_MAX));
	printf("\nOriginal printf (hexadecimal): \n");
	printf("Return value: %i\n", printf("%x %x %x %x %X %X %X %%\n",
		1, -1, 0, 100, 2048, INT_MIN, INT_MAX));
	ft_printf("\nft_printf (pointer): \n");
	ft_printf("Return value: %i\n",
		ft_printf("%p %p %p %p %p %p\n", s1, s2, s3, s4, s5, NULL));
	printf("\nOriginal printf (pointer): \n");
	printf("Return value: %i\n",
		printf("%p %p %p %p %p %p\n", s1, s2, s3, s4, s5, NULL));
	return (0);
}
*/
/*
	ft_printf("\nft_Return value: %i\n", ft_printf("%%% %%%%%x %%"));
	printf("\n   Return value: %i\n", printf("%%% %%%%%x %%"));
*/
/*
int	main(void)
{
	char *str = "bonjour";
	printf("%c%sl%co, %s.\nI am %d years old.\n",
		72, "e", 'l', "world", 31);
	ft_printf("%c%sl%co, %s.\nI am %d years old.\n",
		72, "e", 'l', "world", 31);
	printf("at the address %p, the string %s is stored\n", str, str);
	ft_printf("at the address %p, the string %s is stored\n", str, str);

	printf("  ||  %i\n", printf(" NULL %s NULL", (char *)NULL));
	printf("  ||  %i\n", ft_printf(" NULL %s NULL", (char *)NULL));
  	printf("  ||  %i\n", ft_printf("%p", NULL));
  	printf("  ||  %i\n", printf("%p", NULL));
	printf("%p %p \n", (void *) (void *) 0 , (void *)0);
	ft_printf("%p %p \n", (void *) (void *) 0 , (void *)0);
	printf("  ||  %i\n", ft_printf(" %x ", 0));
	printf("  ||  %i\n", printf(" %x ", 0));
	ft_printf("  %%%%  \n");
	printf("  %%%%  \n");

	printf("  ||  %i\n", ft_printf("\x01\x02\a\v\b\f\r"));
	printf("  ||  %i\n", printf("\x01\x02\a\v\b\f\r"));

	printf("  ||  %i\n", ft_printf(""));
	printf("  ||  %i\n", printf(""));

	printf("  ||  %i\n", ft_printf("%%c"));
	printf("  ||  %i\n", printf("%%c"));

	printf("  ||  %i\n", ft_printf("%%%%%%"));
	printf("  ||  %i\n", printf("%%%%%%"));

	printf("  ||  %i\n", ft_printf("%%%c", 'x'));
	printf("  ||  %i\n", printf("%%%c", 'x'));

	printf("  ||  %i\n", ft_printf("%cc%cc%c", 'a', '\t', 'b'));
	printf("  ||  %i\n", printf("%cc%cc%c", 'a', '\t', 'b'));

	printf("  ||  %i\n", ft_printf("%s", (char *)NULL));
	printf("  ||  %i\n", printf("%s", (char *)NULL));

	printf("  ||  %i\n", ft_printf("%sx", "{} al$#@@@^&$$^#^@@^$*((&"));
	printf("  ||  %i\n", printf("%sx", "{} al$#@@@^&$$^#^@@^$*((&"));

	printf("  ||  %i\n", ft_printf(" %s", "can it handle \t and \n?"));
	printf("  ||  %i\n", printf(" %s", "can it handle \t and \n?"));

	printf("  ||  %i\n", ft_printf("%u", UINT_MAX));
	printf("  ||  %i\n", printf("%u", UINT_MAX));

	printf("  ||  %i\n", ft_printf("%u", -6000023));
	printf("  ||  %i\n", printf("%u", -6000023));

	printf("  ||  %i\n", ft_printf("%X", UINT_MAX));
	printf("  ||  %i\n", printf("%X", UINT_MAX));

	printf("  ||  %i\n", ft_printf("%pp", (void *)LONG_MAX + 423856));
	printf("  ||  %i\n", printf("%pp", (void *)LONG_MAX + 423856));
	printf("  ||  %i\n", ft_printf("%pp", (void *)INT_MAX));
	printf("  ||  %i\n", printf("%pp", (void *)INT_MAX));
	printf("  ||  %i\n", ft_printf("%pp", (void *)0));
	printf("  ||  %i\n", printf("%pp", (void *)0));

	printf("  ||  %i\n", ft_printf("0x%p-", (void *)ULONG_MAX));
	printf("  ||  %i\n", printf("0x%p-", (void *)ULONG_MAX));

	printf("  ||  %i\n", ft_printf("%p", (void *)-14523));
	printf("  ||  %i\n", printf("%p", (void *)-14523));

	printf("  ||  %i\n", ft_printf("%p", ""));
	printf("  ||  %i\n", printf("%p", ""));
}
*/
