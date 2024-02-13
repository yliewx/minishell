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
		return (print_char_err(SYNTAX_ERR, '(', minishell), NULL);
	ft_next_token(minishell);
	*node = ft_ast(minishell, 0);
	if (!*node)
		return (print_str_err(MEM_ERR, NULL, minishell), NULL);
	if (!minishell->curr_token || minishell->curr_token->type != T_CLOSE)
		return (print_str_err(SYNTAX_ERR, "newline", minishell), NULL);
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

void	print_node_and_io(t_node *node)
{
	t_io_node	*list;

	if (node)
		printf("%s\n", node->value);
	list = node->io_list;
	while (list)
	{
		printf("io_list %d-> %s\n", list->type, list->value);
		list = list->next;
	}
}

/* Function to create a new node for command, moves to next token */
t_node	*ft_cmd_handler(t_minishell *shell, t_node **node)
{
	*node = ft_new_node(shell->curr_token->value, \
		shell->curr_token->type, shell);
	if (!*node)
		return (NULL);
	ft_next_token(shell);
	return (*node);
}

/* Function to create single ast node 
- Error if invalid syntax
- Runs parenthesis handler
- If redir occurs before cmd -> create curr cmd node and runs parser redir 
- Else if cmd occurs -> create cmd node and runs parser redir */
t_node	*ft_cmd(t_minishell *shell)
{
	t_node	*node;

	node = NULL;
	if (is_binop(shell->curr_token) || shell->curr_token->type == T_CLOSE)
		return (print_str_err(SYNTAX_ERR, \
			shell->curr_token->value, shell), NULL);
	else if (shell->curr_token->type == T_OPEN)
		parenthesis_handler(shell, &node);
	else
	{
		if (shell->curr_token && is_redir(shell->curr_token))
		{
			if (!ft_redir_helper(shell, &node))
				return (NULL);
		}
		else if (shell->curr_token && shell->curr_token->type == T_STRING)
		{
			if (!ft_cmd_handler(shell, &node))
				return (NULL);
		}
		if (!parser_redir(shell, node))
			return (NULL);
	}
	return (node);
}
