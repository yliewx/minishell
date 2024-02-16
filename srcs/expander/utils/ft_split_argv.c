/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:47:32 by yliew             #+#    #+#             */
/*   Updated: 2024/01/17 16:47:40 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_quote(int c)
{
	return (c == '\'' || c == '\"');
}

/* Function to count the number of tokens in the string
- If in quote: increment i until the closing quote is reached
- Check which comes first after the closing quote: space or new quotes
- If quotes come first: the next quote is considered to be the same word
	- (if there are characters been the closing quote and the space,
	they are considered to belong to the same token as the quoted sequence */
int	count_split_tokens(char *arg, int i, int token_count, int delimiter)
{
	while (arg[i] && !is_whitespace(arg[i]) && !is_quote(arg[i]))
		i++;
	if (arg[i] && is_quote(arg[i]))
	{
		if (is_whitespace(delimiter))
			delimiter = arg[i];
		else if (arg[i] == delimiter)
			delimiter = ' ';
	}
	else if (!arg[i] || (is_whitespace(arg[i]) && is_whitespace(delimiter)
			&& arg[i - 1] && !is_whitespace(arg[i - 1])))
	{
		token_count++;
		if (!arg[i])
			return (token_count);
	}
	i++;
	return (count_split_tokens(arg, i, token_count, delimiter));
}

/* Function to get the length of the substring to be created */
int	get_substr_len(char *arg, int i, int delimiter, bool quote_closed)
{
	while (arg[i] && !is_whitespace(arg[i]) && !is_quote(arg[i]))
		i++;
	if (arg[i] && is_quote(arg[i]))
	{
		if (is_whitespace(delimiter))
		{
			delimiter = arg[i];
			quote_closed = false;
		}
		else if (arg[i] == delimiter)
		{
			delimiter = ' ';
			quote_closed = true;
		}
	}
	if (!arg[i] || (arg[i] == delimiter && quote_closed)
		|| (is_whitespace(arg[i]) && delimiter == ' ' && quote_closed))
		return (i);
	i++;
	return (get_substr_len(arg, i, delimiter, quote_closed));
}

/* Function to create the substrings pointed to by child_argv */
void	assign_argv(char *arg, char ***child_argv, int token_count)
{
	int	delimiter;
	int	start_len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < token_count && arg[i])
	{
		delimiter = ' ';
		while (arg[i] && is_whitespace(arg[i]))
			i++;
		if (is_quote(arg[i]))
			delimiter = arg[i];
		start_len = i++;
		i = get_substr_len(arg, i, delimiter, true);
		(*child_argv)[j++] = ft_substr(arg, start_len, i - start_len);
	}
}

/* Function to split a string by whitespaces, ignoring spaces within quote */
char	**ft_split_argv(char *arg)
{
	char	**child_argv;
	int		token_count;

	if (!arg)
		return (NULL);
	if (!ft_strchr(arg, '\'') && !ft_strchr(arg, '\"'))
		return (ft_split_whitespace(arg));
	token_count = count_split_tokens(arg, 0, 0, ' ');
	child_argv = malloc((token_count + 1) * sizeof(char *));
	if (!child_argv)
		return (NULL);
	assign_argv(arg, &child_argv, token_count);
	child_argv[token_count] = NULL;
	return (child_argv);
}
