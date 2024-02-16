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
	int		quote;
	int		i;
	int		j;
	int		len;

	new_str = malloc(ft_strlen(arg) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i])
	{
		len = i;
		quote = check_if_is_quote(arg, &len, &i);
		while (until_next_quote(arg, len, quote))
			len++;
		while (i < len)
			new_str[j++] = arg[i++];
		i++;
	}
	new_str[j] = '\0';
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
