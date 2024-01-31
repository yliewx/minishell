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

bool	is_builtin_fork(int type)
{
	return (type == CMD_ECHO || type == CMD_ENV || type == CMD_PWD);
}

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

int	exec_builtin(t_node *node, int type, int pid)
{
	if (is_builtin_fork(type))
	{
		if (pid == 0)
		{
			if (type == CMD_ECHO)
				ft_echo(node);
			else if (type == CMD_PWD)
				ft_pwd(node->minishell);
			else if (type == CMD_ENV)
				ft_env(node->minishell);
			exit(node->minishell->exit_status);
		}
		else
			wait(&(node->minishell->exit_status));
	}
	else
	{
		if (type == CMD_CD)
			ft_cd(node->minishell, node);
		else if (type == CMD_EXPORT)
			ft_export(node->minishell, node);
		else if (type == CMD_UNSET)
			ft_unset(node->minishell, node);
		else if (type == CMD_EXIT)
			ft_exit(node->minishell);
	}
	return (1);
}