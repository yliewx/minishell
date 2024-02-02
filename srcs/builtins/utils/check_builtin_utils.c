/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:16:24 by yliew             #+#    #+#             */
/*   Updated: 2024/02/02 16:16:26 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_fork_cmd(int type)
{
	return (type == CMD_ECHO || type == CMD_ENV || type == CMD_PWD || type == CMD_SIMPLE);
}

bool	is_export_without_arg(t_node *node, int type)
{
	return (type == CMD_EXPORT && !node->expanded_arg[1]);
}
