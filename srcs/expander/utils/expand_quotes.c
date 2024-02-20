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

/* Function to return the opening quote if it exists */
char	*get_start_quote(char *c, int quote)
{
	int	i;

	if (!c)
		return (NULL);
	i = 0;
	while (c[i] && c[i] != quote)
		i--;
	if (!c[i])
		return (NULL);
	return (c + i);
}

/* Function to return the closing quote if it exists */
char	*get_end_quote(char *c, int quote)
{
	int	i;

	if (!c)
		return (NULL);
	i = 0;
	while (c[i] && c[i] != quote)
		i++;
	if (!c[i])
		return (NULL);
	return (c + i);
}

/* Function to check whether a character is enclosed by a pair of quotes */
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
bool	skip_quotes(char *c, char *full_arg)
{
	char	*prev_double;
	char	*prev_single;
	int		start_quote;
	int		i;

	i = 0;
	while (c[i] && !is_quote(c[i]))
		i--;
	start_quote = c[i];
	prev_double = get_start_quote(c + i, '\"');
	prev_single = get_start_quote(c + i, '\'');
	if (start_quote == '\'')
	{
		if (prev_single && prev_quotes_closed(c, full_arg, '\''))
			return (false);
		if ((!prev_single || prev_single == c + i) && (!prev_double
				|| prev_quotes_closed(c, full_arg, '\"')))
			return (true);
		if (prev_single < prev_double && !prev_quotes_closed(c, full_arg, '\''))
			return (true);
	}
	else if (start_quote == '\"' && prev_single < prev_double
		&& !prev_quotes_closed(c, full_arg, '\''))
		return (true);
	return (false);
}
