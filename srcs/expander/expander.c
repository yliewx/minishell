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

int	expand_io_value(t_node *node, t_minishell *minishell)
{
	t_io_node	*io_list;

	io_list = node->io_list;
	while (io_list && io_list->value)
	{
		io_list->expanded_arg = ft_strdup(io_list->value);
		if (!io_list->expanded_arg)
			return (print_str_error(MEM_ERR, NULL, minishell));
		check_expandable_var(minishell, &io_list->expanded_arg,
			io_list->expanded_arg);
		check_wildcard(&io_list->expanded_arg, io_list->type, minishell);
		io_list = io_list->next;
	}
	return (0);
}

int	get_expanded_arg(t_node *node)
{
	if (node && node->value)
	{
		node->expanded = ft_strdup(node->value);
		if (!node->expanded)
			return (print_str_error(MEM_ERR, NULL, node->minishell));
		check_expandable_var(node->minishell, &node->expanded, node->expanded);
		check_wildcard(&node->expanded, -1, node->minishell);
		node->expanded_arg = ft_split_argv(node->expanded);
	}
	if (node->io_list && node->io_list->value)
		expand_io_value(node, node->minishell);
	return (0);
}
