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
			return (print_str_err(MEM_ERR, NULL, minishell));
		if (check_expandable_var(minishell, &io_list->expanded_arg,
				io_list->expanded_arg) == -1)
			return (-1);
		if (check_wildcard(&io_list->expanded_arg, io_list->type,
				minishell) == -1)
			return (-1);
		if (remove_expanded_arg_quotes(&io_list->expanded_arg) == -1)
			return (print_str_err(MEM_ERR, NULL, minishell));
		io_list = io_list->next;
	}
	return (0);
}

int	get_expanded_arg(t_node *node, t_minishell *minishell)
{
	if (node && node->value)
	{
		node->expanded = ft_strdup(node->value);
		if (!node->expanded)
			return (print_str_err(MEM_ERR, NULL, minishell));
		if (check_expandable_var(minishell, &node->expanded,
				node->expanded) == -1)
			return (-1);
		if (check_wildcard(&node->expanded, -1, minishell) == -1)
			return (-1);
		node->expanded_arg = ft_split_argv(node->expanded);
		if (!node->expanded_arg)
			return (print_str_err(MEM_ERR, NULL, minishell));
		if (remove_expanded_arg_quotes(node->expanded_arg) == -1)
			return (print_str_err(MEM_ERR, NULL, minishell));
	}
	if (node->io_list && node->io_list->value)
		expand_io_value(node, minishell);
	return (0);
}
