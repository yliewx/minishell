/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:08:07 by agan              #+#    #+#             */
/*   Updated: 2024/02/16 12:08:08 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_iterator(char *line, int *i)
{
	int	count;
	int	in_quote;

	count = 0;
	in_quote = 0;
	while (line[*i] && ((line[*i] != ' ' && !in_quote && !is_symbol(line[*i])) \
		|| (line[*i] == ' ' && in_quote) || (line[*i] != ' ' && in_quote)))
	{
		if (quote_found(line[*i]) && !in_quote)
			in_quote = quote_found(line[*i]);
		else if (quote_found(line[*i]) == in_quote)
			in_quote = 0;
		count++;
		(*i)++;
	}
	return (count);
}

int	command_iterator(char *line, int *i)
{
	int	count;
	int	in_quote;

	count = 0;
	in_quote = 0;
	while (line[*i] && ((!is_symbol(line[*i]) && !in_quote) || \
		(!is_symbol(line[*i]) && in_quote) || \
			(is_symbol(line[*i]) && in_quote)))
	{
		if (quote_found(line[*i]) && !in_quote)
			in_quote = quote_found(line[*i]);
		else if (quote_found(line[*i]) == in_quote)
			in_quote = 0;
		(*i)++;
		count++;
	}
	return (count);
}

int	find_next_token(t_minishell *minishell, char *line, int *i)
{
	int		j;
	t_token	*last;

	last = token_last(minishell->tokens);
	if (last && is_redir(last))
		j = redir_iterator(line, i);
	else
		j = command_iterator(line, i);
	if (is_symbol(line[*i]) && j == 0)
	{
		if (!sym_handler(minishell, line, i))
			return (-1);
	}
	else
	{
		if (j == 0)
			return (0);
		if (!create_str_token(minishell, line, *i, j))
			return (-1);
		if (get_prev_type(minishell->tokens) == T_CLOSE)
			return (print_str_err(SYNTAX_ERR, \
				token_last(minishell->tokens)->value, minishell), -1);
	}
	return (*i);
}
