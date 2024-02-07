/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:50:19 by agan              #+#    #+#             */
/*   Updated: 2024/02/06 17:50:20 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Parenthesis handler runs recursive function within parenthesis
- Checks for syntax error (unclosed parenthesis)*/
t_node	*parenthesis_handler(t_minishell *minishell, t_node **node)
{
	if (!lookahead(minishell))
		return (set_exit_error(minishell, SYNTAX_ERR, 1), \
			print_char_err(minishell, '('), NULL);
	ft_next_token(minishell);
	*node = ft_ast(minishell, 0);
	if (!*node)
		return (set_exit_error(minishell, MEM_ERR, 1), \
			print_str_err(minishell, NULL), NULL);
	if (!minishell->curr_token || minishell->curr_token->type != T_CLOSE)
		return (set_exit_error(minishell, SYNTAX_ERR, 1), \
			print_str_err(minishell, "newline"), NULL);
	ft_next_token(minishell);
	return (*node);
}

/* Function to get curr cmd (after redirects) */
t_token	*get_curr_cmd(t_minishell *minishell)
{
	t_token	*ret_token;

	ret_token = minishell->curr_token;
	while (ret_token && is_redir(ret_token))
	{
		ret_token = ret_token->next;
		if (ret_token->next && is_redir(ret_token->next))
			ret_token = ret_token->next;
	}
	if (ret_token->next && ret_token->next->type == T_STRING)
		return (ret_token->next);
	else
		return (NULL);
}

/* Function to create single ast node 
- Error if invalid syntax
- Runs parenthesis handler
- If redir occurs before cmd -> create curr cmd node and runs parser redir 
- Else if cmd occurs -> create cmd node and runs parser redir */
t_node	*ft_cmd(t_minishell *minishell)
{
	t_node	*node;

	node = NULL;
	if (is_binop(minishell->curr_token) || \
		minishell->curr_token->type == T_CLOSE)
		return (set_exit_error(minishell, SYNTAX_ERR, 1), \
			print_str_err(minishell, minishell->curr_token->value), NULL);
	else if (minishell->curr_token->type == T_OPEN)
		parenthesis_handler(minishell, &node);
	else
	{
		if (minishell->curr_token && is_redir(minishell->curr_token))
		{
			if (!ft_redir_helper(minishell, &node))
				return (NULL);
		}
		else if (minishell->curr_token && \
			minishell->curr_token->type == T_STRING)
		{
			node = ft_new_node(minishell->curr_token->value, minishell->curr_token->type, minishell);
			if (!node)
				return (NULL);
			ft_next_token(minishell);
		}
		if (!parser_redir(minishell, node))
			return (NULL);
	}
	return (node);
}
