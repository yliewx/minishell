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
		while (lst->value && lst->value[++i])
		{
			if (lst->value[i] == '\'' || lst->value[i] == '\"')
			{
				end_quote = ft_strrchr(&lst->value[i], lst->value[i]);
				if (end_quote == &(lst->value[i]))
					return (print_char_err(SYNTAX_ERR, lst->value[i], \
						minishell), -1);
				else
					i = end_quote - lst->value;
			}
		}
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
