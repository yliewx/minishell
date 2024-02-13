/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:15:42 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 17:15:50 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_fork_builtin(t_node *node, t_minishell *minishell, int type, int pid)
{
	if (pid == 0)
	{
		if (type == CMD_ECHO)
			ft_echo(node);
		else if (type == CMD_PWD)
			ft_pwd(minishell);
		else if (type == CMD_ENV)
			ft_env(minishell);
		else if (type == CMD_EXPORT)
			ft_export(minishell, node);
		exit(minishell->exit_status);
	}
	else
	{
		wait(&(minishell->exit_status));
		minishell->exit_status = WEXITSTATUS(minishell->exit_status);
	}
	return (0);
}

int	exec_builtin(t_node *node, int type, int pid)
{
	if (is_fork_cmd(node, type))
		exec_fork_builtin(node, node->minishell, type, pid);
	else
	{
		if (type == CMD_CD)
			ft_cd(node->minishell, node);
		else if (type == CMD_EXPORT)
			ft_export(node->minishell, node);
		else if (type == CMD_UNSET)
			ft_unset(node->minishell, node);
		else if (type == CMD_EXIT)
			ft_exit(node->minishell, node);
	}
	return (0);
}
