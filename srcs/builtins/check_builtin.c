/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:15:42 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 17:15:50 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	exec_builtin(t_node *node, int type)
{
	if (type == CMD_ECHO)
		return (ft_echo(node));
	else if (type == CMD_CD)
		return (ft_cd(node->minishell, node));
	else if (type == CMD_PWD)
		return (ft_pwd(node->minishell));
	else if (type == CMD_EXPORT)
		return (ft_export(node->minishell, node));
	else if (type == CMD_UNSET)
		return (ft_unset(node->minishell, node));
	else if (type == CMD_ENV)
		return (ft_env(node->minishell));
	else if (type == CMD_EXIT)
		return (ft_exit(node->minishell));
	return (1);
}