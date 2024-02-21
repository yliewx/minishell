/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:08:59 by yliew             #+#    #+#             */
/*   Updated: 2024/02/05 18:09:01 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to check whether the previous quotes are closed
(to determine if the current quote is part of the previous quoted sequence)
- Returns true if the previous quote count is divisible by 2 */
bool	prev_quotes_closed(char *c, char *full_arg, int quote)
{
	int	count;

	count = 0;
	while (c && c >= full_arg)
	{
		if (*c == quote)
			count++;
		c--;
	}
	return (count % 2 == 0);
}

/* Function to check whether the contents of the quoted sequence
should be expanded

echo '$HOME' -> DOES NOT expand
echo "$HOME" -> EXPANDS

echo 'hello world "$HOME"' -> DOES NOT expand
	bash:		hello world "$HOME"

echo 'hello world '$HOME'' -> EXPANDS
echo "hello world "$HOME"" -> EXPANDS
	bash:		hello world /home/user

echo "hello world '$HOME'" -> EXPANDS
	bash:		hello world '/home/user'

- Return false = do not skip quote; variable will be expanded
- Return true = skip quote; variable will not be expanded */
