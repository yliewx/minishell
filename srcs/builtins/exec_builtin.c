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

int	exec_builtin_type(t_node *node, int builtin_type, t_node *parent_node)
{
	if (builtin_type == CMD_ECHO)
		ft_echo(node);
	else if (builtin_type == CMD_PWD)
		ft_pwd(node->minishell);
	else if (builtin_type == CMD_ENV)
		ft_env(node->minishell);
	else if (builtin_type == CMD_CD)
		ft_cd(node->minishell, node);
	else if (builtin_type == CMD_EXPORT)
		ft_export(node->minishell, node);
	else if (builtin_type == CMD_UNSET)
		ft_unset(node->minishell, node);
	else if (builtin_type == CMD_EXIT && parent_node->type != T_PIPE)
		ft_exit(node->minishell, node);
	return (0);
}

int	exec_fork_builtin(t_node *node, int builtin_type, int pid, \
	t_node *parent_node)
{
	if (pid == 0)
	{
		exec_builtin_type(node, builtin_type, parent_node);
		free_data_and_exit(node->minishell);
	}
	else
	{
		waitpid(pid, &(node->minishell->exit_status), 0);
		ft_exit_status(node->minishell);
	}
	return (0);
}

int	exec_builtin(t_node *node, int builtin_type, int pid, \
	t_node *parent_node)
{
	if (parent_node->type == T_PIPE || is_fork_cmd(node, builtin_type))
		exec_fork_builtin(node, builtin_type, pid, parent_node);
	else
	{
		if (pid == 0)
			free_data_and_exit(node->minishell);
		exec_builtin_type(node, builtin_type, parent_node);
	}
	return (0);
}
