/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:58:48 by yliew             #+#    #+#             */
/*   Updated: 2024/01/17 17:58:54 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Functions to remove all paired quotes from an arg
(excluding single quotes that are nested inside double quotes & vice versa)
- If a quote is found, reads until the end quote, then copies the contents
of the quoted sequence into the new string */

bool	until_next_quote(char *arg, int len, int quote)
{
	return ((quote != 0 && arg[len] && arg[len] != quote)
		|| (quote == 0 && arg[len] && !is_quote(arg[len])));
}

int	check_if_is_quote(char *arg, int *len, int *i)
{
	int	quote;

	if (is_quote(arg[*len]))
	{
		quote = arg[*len];
		(*len)++;
		(*i)++;
		return (quote);
	}
	return (0);
}

char	*remove_quotes(char *arg)
{
	char	*new_str;
	char	*end_quote;
	int		quote;
	int		i;

	new_str = ft_calloc(ft_strlen(arg), sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (*arg)
	{
		quote = 0;
		while (*arg && !is_quote(*arg))
		{
			new_str[i++] = *arg;
			arg++;
		}
		if (*arg && is_quote(*arg))
		{
			quote = *arg;
			arg++;
			end_quote = get_end_quote(arg, quote);
			while (*arg && arg != end_quote)
			{
				new_str[i++] = *arg;
				arg++;
			}
			arg++;
		}
	}
	new_str[i] = '\0';
	return (new_str);
}

int	remove_expanded_arg_quotes(char **arg)
{
	char	*temp;

	if (ft_strchr(*arg, '\'') || ft_strchr(*arg, '\"'))
	{
		temp = *arg;
		*arg = remove_quotes(temp);
		if (!*arg)
			return (-1);
		free(temp);
	}
	return (0);
}

int	remove_expanded_argv_quotes(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (remove_expanded_arg_quotes(&argv[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
