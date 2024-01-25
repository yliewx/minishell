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

// Print token list - For tests
void print_token_list(t_token *token_list)
{
	while(token_list)
	{
		printf("%s\n", token_list->value);
		printf("%i\n", token_list->type);
		token_list = token_list->next;
	}
}

void skip_spaces(char *line, int *i)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
}

// Checks if is symbol
int is_symbol(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')')
		return (1);
	return (0);
}


