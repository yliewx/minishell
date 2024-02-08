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

// Exec_simple_cmd
    // Split and expand cmd
    // Fork
    // Exec
void exec_simple_cmd(t_node *node, char **argv, t_minishell *minishell, int pid)
{
	char *command_path;

	(void)node;
	command_path = NULL;
	if (pid == 0)
	{
		get_command_path(&command_path, argv[0], minishell);
		if (minishell->minishell_err != NO_ERR)
			exit(EXIT_FAILURE);
		if (execve(command_path, argv, minishell->envp) == -1)
		{
			exec_error(FILE_NOT_FOUND_ERR, argv[0], minishell);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&(minishell->exit_status));
	}
}

// Function to check for echo, env, pwd
void exec_command(t_node *node, t_minishell *minishell)
{
	int pid;
	int pipefd[2];
	int builtin_type;

	pid = -1;
	builtin_type = -1;
	get_expanded_arg(node);
	if (minishell->minishell_err != NO_ERR)
		return ;
	builtin_type = check_builtin(node);
	if (node->next_binop == T_PIPE)
		pipe(pipefd);
	if (is_fork_cmd(node, builtin_type))
		pid = fork();
	if (redir_handler(node, pid, pipefd) == -1)
		return ;
	if (builtin_type != CMD_SIMPLE)
	{
		exec_builtin(node, builtin_type, pid);
	}
	else
	{
		exec_simple_cmd(node, node->expanded_arg, minishell, pid);
	}
}