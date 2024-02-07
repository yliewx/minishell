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

void	expand_io_value(t_node *node, t_minishell *minishell)
{
	t_io_node	*io_list;

	io_list = node->io_list;
	while (io_list && io_list->value)
	{
		check_expandable_var(minishell, &io_list->value, io_list->value);
		check_wildcard(&io_list->value, &io_list->expanded_arg, io_list->type,
			minishell);
		io_list = io_list->next;
	}
}

void	get_expanded_arg(t_node *node)
{
	if (node && node->value)
	{
		check_expandable_var(node->minishell, &node->value, node->value);
		check_wildcard(&node->value, &node->expanded, -1, node->minishell);
		if (node->expanded)
			node->expanded_arg = ft_split_argv(node->expanded);
		else
			node->expanded_arg = ft_split_argv(node->value);
	}
	if (node->io_list && node->io_list->value)
		expand_io_value(node, node->minishell);
}