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

int quote_found(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

int	command_iterator(char *line, int *i, t_token *last)
{
	int	count;
	int in_quote;

	count = 0;
	in_quote = 0;
	if (last && is_redir(last))
	{
		while (line[*i] && line[*i] != ' ')
		{
			count++;
			(*i)++;
		}
	}
	else
	{
		while (line[*i] && ((!is_symbol(line[*i]) && !in_quote) || \
			(!is_symbol(line[*i]) && in_quote) || (is_symbol(line[*i]) && in_quote)))
		{
			if (quote_found(line[*i]) && !in_quote)
				in_quote = quote_found(line[*i]);
			else if (quote_found(line[*i]) == in_quote)
				in_quote = 0;
			(*i)++;
			count++;
		}
	}
	return (count);
}

int	find_next_token(t_minishell *minishell, char *line, int *i)
{
	int		j;
	t_token	*last;

	last = token_last(minishell->tokens);
	j = command_iterator(line, i, last);
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
int	quotes_checker(t_minishell *minishell, t_token *token_list)
{
	t_token	*lst;
	int		i;
	char	*end_quote;

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
						return (print_char_err(SYNTAX_ERR, lst->value[i], \
							minishell), -1);
					else
						i = end_quote - lst->value;
				}
			}
		}
		lst = lst->next;
	}
	return (0);
}
