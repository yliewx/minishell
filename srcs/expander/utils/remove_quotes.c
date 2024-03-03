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

/* Function to return the closing quote if it exists */
char	*get_end_quote(char *c, int quote)
{
	int	i;

	if (!c)
		return (NULL);
	i = 0;
	if (c[i] == quote)
		i++;
	while (c[i] && c[i] != quote)
		i++;
	if (!c[i])
		return (NULL);
	return (c + i);
}

/* Functions to remove all paired quotes from an arg
(excluding single quotes that are nested inside double quotes & vice versa)
- If a quote is found, reads until the end quote, then copies the contents
of the quoted sequence into the new string */
char	*remove_quotes(char *arg)
{
	char	*new_str;
	char	*end_quote;
	int		i;

	new_str = ft_calloc(ft_strlen(arg), sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (*arg)
	{
		while (*arg && !is_quote(*arg))
			new_str[i++] = *arg++;
		if (*arg && is_quote(*arg))
		{
			end_quote = get_end_quote(arg, *arg);
			arg++;
			while (*arg && arg != end_quote)
				new_str[i++] = *arg++;
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
