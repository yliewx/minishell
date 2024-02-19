/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:56:43 by yliew             #+#    #+#             */
/*   Updated: 2024/01/29 11:24:05 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to recursively traverse tree to exec nodes 
- When binop found, traverse left
- If exist status fulfilled, traverse right
- Leaf node -> exec command */
t_node	*traverse_tree(t_node *ast, t_minishell *minishell, \
	t_token_type parent_type)
{
	if (!ast || minishell->minishell_err)
		return (ast);
	if (is_binop_node(ast))
	{
		traverse_tree(ast->left, minishell, ast->type);
		if ((!minishell->exit_status && ast->type == T_AND) \
			|| (minishell->exit_status && ast->type == T_OR)
			|| ast->type == T_PIPE)
			traverse_tree(ast->right, minishell, ast->type);
	}
	else
		exec_command(ast, minishell, parent_type);
	return (ast);
}

/* Function to create heredoc nodes and start traversal */
t_node	*ft_exec(t_minishell *minishell)
{
	if (minishell->heredoc_count >= 1)
		ft_heredoc(minishell->heredoc_list, minishell);
	if (minishell->ast && !g_signal.sigint_heredoc && !minishell->minishell_err)
		traverse_tree(minishell->ast, minishell, minishell->ast->type);
	return (minishell->ast);
}
