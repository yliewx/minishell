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
	if (pid == 0)
	{
		get_command_path(&command_path, argv[0], minishell);
		if (minishell->minishell_err != NO_ERR)
			free_data_and_exit(minishell);
		if (execve(command_path, argv, minishell->envp) == -1)
		{
			exec_error(FILE_NOT_FOUND_ERR, argv[0], minishell);
			free_data_and_exit(minishell);
		}
	}
	else
	{
		waitpid(pid, &(minishell->exit_status), 0);
		minishell->exit_status = WEXITSTATUS(minishell->exit_status);
	}
}

/* Function to exec command
- Expand args
- Pipe and fork if necessary
- Exec builtin or simple cmd */
void	exec_command(t_node *node, t_minishell *minishell)
{
	int	pid;
	int	pipefd[2];
	int	builtin_type;

	pid = -1;
	builtin_type = -1;
	if (minishell->minishell_err)
		return ;
	get_expanded_arg(node, minishell);
	builtin_type = check_builtin(node);
	if (pipe_handler(pipefd, node, minishell))
		return ;
	if (fork_handler(&pid, builtin_type, node, minishell))
		return ;
	if (minishell->minishell_err || redir_handler(node, pid, pipefd) == -1)
	{
		if (pid == 0)
			free_data_and_exit(minishell);
		return ;
	}
	if (builtin_type != CMD_SIMPLE)
		exec_builtin(node, builtin_type, pid);
	else
		exec_simple_cmd(node->expanded_arg, minishell, pid);
}
