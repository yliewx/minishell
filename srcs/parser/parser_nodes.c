/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:47:53 by agan              #+#    #+#             */
/*   Updated: 2024/01/25 16:47:54 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_init(t_node *node, char *cmd)
{
	node->expanded = NULL;
	node->expanded_arg = NULL;
	node->left = NULL;
	node->right = NULL;
	node->io_list = NULL;
	if (cmd)
		node->value = ft_strdup(cmd);
	else
		node->value = NULL;
}

// Create ast nodes
t_node	*ft_new_node(char *cmd, t_token_type type, t_minishell *minishell)
{
	t_node	*node;
	t_token	*next_binop_node;

	node = malloc(sizeof(t_node) * 1);
	if (!node)
		return (print_str_err(MEM_ERR, NULL, minishell), NULL);
	node_init(node, cmd);
	node->type = type;
	node->minishell = minishell;
	if (lookahead(minishell))
	{
		next_binop_node = next_binop(minishell);
		if (next_binop_node)
			node->next_binop = next_binop_node->type;
		else
			node->next_binop = T_NULL;
	}
	else
		node->next_binop = T_NULL;
	return (node);
}
