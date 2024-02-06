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

void	get_expanded_arg(t_node *node)
{
	if (node && node->value)
	{
		check_expandable_var(node->minishell, &node->value, node->value);
		check_wildcard(&node->value, &node->expanded);
		if (node->expanded)
			node->expanded_arg = ft_split_argv(node->expanded);
		else
			node->expanded_arg = ft_split_argv(node->value);
	}
	if (node->io_list && node->io_list->value)
	{
		check_expandable_var(node->minishell, &node->io_list->value,
			node->io_list->value);
		if (is_ambiguous_redir(node->io_list))
			expander_error(AMBIG_REDIR_ERR, node->io_list->value,
				node->minishell);
		else
			check_wildcard(&node->io_list->value, &node->io_list->expanded_arg);
	}
}