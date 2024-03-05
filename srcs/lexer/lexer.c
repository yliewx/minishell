/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:18:08 by agan              #+#    #+#             */
/*   Updated: 2024/01/11 19:18:09 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Runs lexer function on command
Iterates through command line
Skips spaces and finds next token to tokenize
After tokenization, runs quote checker to check for unclosed quotes
*/
t_token	*ft_lexer(t_minishell *minishell, char *line)
{
	int	i;

	i = 0;
	if (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			return (NULL);
	}
	while (line[i])
	{
		skip_spaces(line, &i);
		if (find_next_token(minishell, line, &i) == -1)
			return (NULL);
	}
	if (quotes_checker(minishell, minishell->tokens) == -1 || \
		syntax_checker(minishell, minishell->tokens) == -1)
		return (NULL);
	return (minishell->tokens);
}
