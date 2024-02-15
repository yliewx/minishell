/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:05:08 by agan              #+#    #+#             */
/*   Updated: 2024/01/15 16:05:09 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Skips spaces */
void	skip_spaces(char *line, int *i)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
}

/* Checks if symbol found */
int	is_symbol(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')')
		return (1);
	return (0);
}

/* Gets second last token's type */
t_token_type	get_prev_type(t_token *token_list)
{
	t_token	*last;

	last = token_last(token_list);
	if (!(last->prev))
		return (T_STRING);
	else
		return (last->prev->type);
}

/* Returns int for single/double quote found */
int	quote_found(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

/* Print token list */
void	print_token_list(t_token *token_list)
{
	while (token_list)
	{
		printf("%s\n", token_list->value);
		printf("%i\n", token_list->type);
		token_list = token_list->next;
	}
}
