/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:16:24 by yliew             #+#    #+#             */
/*   Updated: 2024/02/02 16:16:26 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Utils functions to check whether the builtin should be
executed in a child process*/
bool	is_export_without_arg(t_node *node, int type)
{
	return (type == CMD_EXPORT && !node->expanded_arg[1]);
}

bool	is_fork_cmd(t_node *node, int type)
{
	return (type == CMD_ECHO || type == CMD_ENV || type == CMD_PWD
		|| type == CMD_SIMPLE || is_export_without_arg(node, type));
}

/* Function to return the builtin type
- Return simple command if it is not a builtin*/
int	check_builtin(t_node *node)
{
	if (ft_strncmp(node->expanded_arg[0], "echo", 5) == 0)
		return (CMD_ECHO);
	else if (ft_strncmp(node->expanded_arg[0], "cd", 3) == 0)
		return (CMD_CD);
	else if (ft_strncmp(node->expanded_arg[0], "pwd", 4) == 0)
		return (CMD_PWD);
	else if (ft_strncmp(node->expanded_arg[0], "export", 7) == 0)
		return (CMD_EXPORT);
	else if (ft_strncmp(node->expanded_arg[0], "unset", 6) == 0)
		return (CMD_UNSET);
	else if (ft_strncmp(node->expanded_arg[0], "env", 4) == 0)
		return (CMD_ENV);
	else if (ft_strncmp(node->expanded_arg[0], "exit", 5) == 0)
		return (CMD_EXIT);
	return (CMD_SIMPLE);
}
