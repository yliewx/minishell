/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:52:12 by agan              #+#    #+#             */
/*   Updated: 2024/02/01 15:52:13 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to remove first node of heredoc list */
void	remove_heredoc_node(t_heredoc **list)
{
	t_heredoc	*to_free;

	to_free = *list;
	if (to_free)
	{
		*list = (*list)->next;
		free(to_free->delimiter);
		free(to_free);
	}
}

void	heredoc_warning(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by " \
		"end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

/* Reads heredoc input and writes to heredoc pipe */
void	exec_heredoc(t_minishell *shell, int pid, t_heredoc *node, char *line)
{
	if (pid == 0)
	{
		g_signal.in_heredoc = true;
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				heredoc_warning(node->delimiter);
				break ;
			}
			if (!ft_strncmp(line, node->delimiter, ft_strlen(line)) \
				&& (ft_strlen(line) == ft_strlen(node->delimiter)))
			{
				free(line);
				break ;
			}
			ft_putstr_fd(line, node->pipefd[1]);
			ft_putstr_fd("\n", node->pipefd[1]);
			free(line);
		}
		free_data_and_exit(shell);
	}
	waitpid(pid, &(shell->exit_status), 0);
	shell->exit_status = WEXITSTATUS(shell->exit_status);
}

/* Function to create pipes for each heredoc node
- Fork child process
- Exec heredoc within child process */
int	ft_heredoc(t_heredoc *list, t_minishell *shell)
{
	t_heredoc	*node;
	int			pid;
	char		*line;

	line = NULL;
	node = list;
	while (node && !g_signal.sigint)
	{
		if (pipe(node->pipefd) == -1)
			return (print_str_err(PIPE_ERR, \
				"error: pipe() failed\n", shell), -1);
		pid = fork();
		if (pid == -1)
			return (print_str_err(FORK_ERR, \
				"error: fork() failed\n", shell), -1);
		exec_heredoc(shell, pid, node, line);
		node = node->next;
	}
	return (0);
}

// /* Function to pipe heredoc input */
// int	ft_heredoc(t_heredoc *list, t_minishell *shell)
// {
// 	int			pid;

// 	pid = fork();
// 	if (pid == -1)
// 		return (print_str_err(FORK_ERR, "error: fork() failed\n", shell), -1);
// 	if (pid == 0)
// 	{
// 		g_signal.in_heredoc = true;
// 		exec_heredoc(list, shell);
// 		exit(0);
// 	}
// 	waitpid(pid, &(shell->exit_status), 0);
// 	shell->exit_status = WEXITSTATUS(shell->exit_status);
// 	return (0);
// }
