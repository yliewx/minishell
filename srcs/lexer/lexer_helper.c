/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:57:57 by agan              #+#    #+#             */
/*   Updated: 2024/01/25 16:57:57 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to find the next token (symbol or string) */
// int find_next_token(t_minishell *minishell, char *line, int *i)
// {
// 	int j;

// 	j = 0;
// 	while (line[*i] && !is_symbol(line[*i]))
// 	{
// 		j++;
// 		(*i)++;
// 	}
// 	if (is_symbol(line[*i]) && j == 0)
// 	{
// 		if (!sym_handler(minishell, line, i))
// 			return (-1);
// 	}
// 	else
// 	{
// 		if (!create_str_token(minishell, line, *i, j))
// 			return (-1);
// 	}
// 	return (*i);
// }

int find_next_token(t_minishell *minishell, char *line, int *i)
{
	int j;
	t_token *last;

	j = 0;
	last = token_last(minishell->tokens);
	if (last && is_redir(last))
	{
		while (line[*i] && line[*i] != ' ')
		{
			j++;
			(*i)++;
		}
	}
	else
	{
		while (line[*i] && !is_symbol(line[*i]))
		{
			j++;
			(*i)++;
		}
	}
	if (is_symbol(line[*i]) && j == 0)
	{
		if (!sym_handler(minishell, line, i))
			return (-1);
	}
	else
	{
		if (!create_str_token(minishell, line, *i, j))
			return (-1);
	}
	return (*i);
}

/* Function to check for unclosed quote in values within token_list */
int quotes_checker(t_minishell *minishell, t_token *token_list)
{
	t_token *lst;
	int i;
	char *end_quote;

	lst = token_list;
	while (lst)
	{
		i = -1;
		if (lst->value)
		{
			while (lst->value[++i])
			{
				if (lst->value[i] == '\'' || lst->value[i] == '\"')
				{
					if (lst->value[i] == '\'')
						end_quote = ft_strrchr(&lst->value[i], '\'');
					else if (lst->value[i] == '\"')
						end_quote = ft_strrchr(&lst->value[i], '\"');
					if (end_quote == &(lst->value[i]))
						return (set_exit_error(minishell, SYNTAX_ERR, 1), \
							print_char_err(minishell, lst->value[i]), -1);
					else
						i = end_quote - lst->value;
				}
			}
		}
		lst = lst->next;
	}
	return (0);
}