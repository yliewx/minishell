/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:17:55 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 19:18:01 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_node_arg(t_node_arg *node_arg, t_minishell *minishell, int io_type)
{
	node_arg->io_type = io_type;
	node_arg->minishell = minishell;
	node_arg->in_quote = 0;
}

/* Function to handle the expansion of io list values */
int	expand_io_value(t_node *node, t_minishell *minishell)
{
	t_io_node	*io_list;
	t_node_arg	node_arg;

	io_list = node->io_list;
	while (io_list && io_list->value)
	{
		io_list->expanded_arg = ft_strdup(io_list->value);
		if (!io_list->expanded_arg)
			return (print_str_err(MEM_ERR, NULL, minishell), -1);
		init_node_arg(&node_arg, minishell, io_list->type);
		if (ft_expand_quote_handler(&io_list->expanded_arg,
				io_list->expanded_arg, &node_arg) == -1)
			return (-1);
		if (remove_expanded_arg_quotes(&io_list->expanded_arg) == -1)
			return (print_str_err(MEM_ERR, NULL, minishell), -1);
		io_list = io_list->next;
	}
	return (0);
}

/* Function to handle the expansion of the node's argument value */
int	get_expanded_arg(t_node *node, t_minishell *minishell)
{
	t_node_arg	node_arg;

	if (node && node->value)
	{
		node->expanded = ft_strdup(node->value);
		if (!node->expanded)
			return (print_str_err(MEM_ERR, NULL, minishell), -1);
		init_node_arg(&node_arg, minishell, -1);
		if (ft_expand_quote_handler(&node->expanded,
				node->expanded, &node_arg) == -1)
			return (-1);
		node->expanded_arg = ft_split_argv(node->expanded);
		if (!node->expanded_arg)
			return (print_str_err(MEM_ERR, NULL, minishell), -1);
		if (remove_expanded_argv_quotes(node->expanded_arg) == -1)
			return (print_str_err(MEM_ERR, NULL, minishell), -1);
	}
	if (node->io_list && node->io_list->value)
	{
		if (expand_io_value(node, minishell) == -1)
			return (-1);
	}
	return (0);
}
