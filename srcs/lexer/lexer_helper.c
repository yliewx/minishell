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

/* Function to set unclosed quote and opening quote variables */
void	quote_helper(int *unclosed, int *quote, char c, int within_quote)
{
	if (!within_quote)
	{
		*unclosed = 0;
		*quote = 0;
	}
	else
	{
		*quote = quote_found(c);
		*unclosed = 1;
	}
}

/* Function to check for unclosed quote in values within token_list */
int	quotes_checker(t_minishell *minishell, t_token *token_list)
{
	t_token	*lst;
	int		i;
	int		unclosed;
	int		quote;

	lst = token_list;
	quote = 0;
	unclosed = 0;
	while (lst)
	{
		i = -1;
		while (lst->value && lst->value[++i])
		{
			if (quote && quote == quote_found(lst->value[i]))
				quote_helper(&unclosed, &quote, lst->value[i], 0);
			else if (!quote && quote_found(lst->value[i]))
				quote_helper(&unclosed, &quote, lst->value[i], 1);
		}
		if (unclosed)
			return (print_char_err(SYNTAX_ERR, lst->value[i - 1], \
				minishell), -1);
		lst = lst->next;
	}
	return (0);
}

/* Function to check if there is a redir value */
int	redir_checker(t_minishell *minishell, t_token *token_list)
{
	t_token	*lst;

	lst = token_list;
	while (lst)
	{
		if (type_checker(lst->type) == L_REDIR)
			if (!lst->next)
				return (print_str_err(SYNTAX_ERR, "newline", minishell), -1);
		lst = lst->next;
	}
	return (0);
}
