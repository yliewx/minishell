/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:55:16 by agan              #+#    #+#             */
/*   Updated: 2024/02/01 15:55:16 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to exec simple command
- Get command path
- Exec in child process */
void	exec_simple_cmd(char **argv, t_minishell *minishell, int pid)
{
	char	*command_path;

	command_path = NULL;
	exec_signal_handler(pid);
	if (pid == 0)
	{
		get_command_path(&command_path, argv[0], minishell);
		if (minishell->minishell_err != NO_ERR)
			free_data_and_exit(minishell);
		if (execve(command_path, argv, minishell->envp) == -1)
		{
			if (is_directory(argv[0]))
				exec_error(DIR_ERR, argv[0], minishell);
			else
				exec_error(FILE_NOT_FOUND_ERR, argv[0], minishell);
			free_data_and_exit(minishell);
		}
	}
	else
	{
		waitpid(pid, &(minishell->exit_status), 0);
		ft_exit_status(minishell);
	}
}

/* Function to exec command
- Expand args
- Pipe and fork if necessary
- Exec builtin or simple cmd */
void	exec_command(t_node *node, t_minishell *minishell, \
	t_node *parent_node)
{
	int	pid;
	int	builtin_type;

	pid = -1;
	builtin_type = -1;
	if (minishell->minishell_err)
		return ;
	if ((get_expanded_arg(node, minishell) == -1)
		|| fork_handler(&pid, minishell) == -1)
		return ;
	builtin_type = check_builtin(node);
	if (redir_handler(node, pid) == -1 \
		|| minishell->minishell_err || node->type == T_NULL)
	{
		if (pid == 0)
			free_data_and_exit(minishell);
		waitpid(pid, &(minishell->exit_status), 0);
		ft_exit_status(minishell);
		return ;
	}
	if (builtin_type != CMD_SIMPLE)
		exec_builtin(node, builtin_type, pid, parent_node);
	else
		exec_simple_cmd(node->expanded_arg, minishell, pid);
}
