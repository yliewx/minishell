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

int	count_split_tokens(char *arg)
{
	int	token_count;
	int	in_quote;
	int	i;

	token_count = 0;
	in_quote = 0;
	i = 0;
	while (arg[i])
	{
		if ((arg[i] == '\'' || arg[i] == '\"') && in_quote == 0)
			in_quote = arg[i];
		else if (arg[i] == in_quote)
			in_quote = 0;
		if (arg[i] != ' ' && (arg[i + 1] == ' ' || !(arg[i + 1]))
			&& in_quote == 0)
			token_count++;
		i++;
	}
	return (token_count);
}

int	get_substr_len(char *arg, int delimiter, int i)
{
	while (arg[i] && arg[i] != delimiter)
		i++;
	if ((arg[i] == '\'' || arg[i] == '\"') && arg[i + 1] != ' ')
	{
		i++;
		while (arg[i] && arg[i] != delimiter)
			i++;
	}
	return (i);
}

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
		while (arg[i] && arg[i] == delimiter)
			i++;
		if (arg[i] == '\'' || arg[i] == '\"')
			delimiter = arg[i];
		start_len = i++;
		i = get_substr_len(arg, delimiter, i);
		(*child_argv)[j++] = ft_substr(arg, start_len, i - start_len);
		i++;
	}
}

char	**ft_split_argv(char *arg)
{
	char	**child_argv;
	int	token_count;

	token_count = count_split_tokens(arg);
	child_argv = malloc((token_count + 1) * sizeof(char *));
	if (!child_argv)
	{
		perror("Failed to allocate memory for child_argv\n");
		return (NULL);
	}
	assign_argv(arg, &child_argv, token_count);
	child_argv[token_count] = NULL;
	return (child_argv);
}
