/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:15:01 by yliew             #+#    #+#             */
/*   Updated: 2023/09/16 16:17:37 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int		ft_printf(const char *str, ...);
void	ft_putchar(int c, int *len);
void	ft_putstr(char *str, int *len);
void	ft_putnbr(int n, int *len);
void	ft_putunsigned(unsigned int n, int *len);
void	ft_puthex(size_t n, const char *base, int *len);
void	ft_putptr(size_t p, const char *base, int *len);

#endif
