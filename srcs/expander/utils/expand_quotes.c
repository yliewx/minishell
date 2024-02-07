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

/*
echo '$HOME' -> DOES NOT expand
echo "$HOME" -> EXPANDS

echo 'hello world "$HOME"' -> DOES NOT expand
	bash:		hello world "$HOME"
	minishell:	hello world "$HOME"

echo 'hello world '$HOME'' -> EXPANDS
	bash:		hello world /home/user
	minishell:	hello world /home/user

echo "hello world '$HOME'" -> EXPANDS
	bash:		hello world '/home/user'
	minishell:	hello world '/home/user'

echo "hello world "$HOME"" -> EXPANDS
	bash:		hello world /home/user
	minishell:	hello world /home/user

echo hello '$HOME' world "$HOME" ''$HOME'' $USER "$PWD"
*/
char	*get_start_quote(char *c, int quote)
{
	int	i;

	i = 0;
	while (c[i] && c[i] != quote)
		i--;
	if (!c[i])
		return (NULL);
	return (c + i);
}

char	*get_end_quote(char *c, int quote)
{
	int	i;

	i = 0;
	while (c[i] && c[i] != quote)
		i++;
	if (!c[i])
		return (NULL);
	return (c + i);
}

bool	is_in_quote(char *c, int quote)
{
	char	*start_quote;
	char	*end_quote;

	if (!c)
		return (false);
	start_quote = get_start_quote(c, quote);
	end_quote = get_end_quote(c + 1, quote);
	return (start_quote && end_quote);
}

bool	prev_quotes_are_closed(char *c, char *full_arg, int quote)
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

/*return false = do not skip quote; variable will be expanded
return true = skip quote; variable will not be expanded*/
bool	skip_quotes(char *c, char *full_arg)
{
	char	*prev_double_quote;
	char	*prev_single_quote;
	int		start_quote;
	int		i;

	if (!ft_strchr(c, '\''))
		return (false);
	start_quote = 0;
	i = 0;
	while (c[i] && !is_quote(c[i]))
		i--;
	start_quote = c[i];
	prev_double_quote = get_start_quote(c + i, '\"');
	prev_single_quote = get_start_quote(c + i, '\'');
	if (start_quote == '\'')
	{
		if (prev_single_quote && prev_quotes_are_closed(c, full_arg, '\''))
			return (false);
		if ((!prev_single_quote || prev_single_quote == c + i)
			&& (!prev_double_quote || prev_quotes_are_closed(c, full_arg, '\"')))
			return (true);
		if (prev_single_quote < prev_double_quote)
		{
			if (!prev_quotes_are_closed(c, full_arg, '\''))
				return (true);
		}
	}
	else if (start_quote == '\"')
	{
		if (prev_single_quote < prev_double_quote
			&& !prev_quotes_are_closed(c, full_arg, '\''))
			return (true);
	}
	return (false);
}
