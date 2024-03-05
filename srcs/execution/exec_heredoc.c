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

/* Function to check if io node is last heredoc node in io_list */
int	heredoc_count(t_io_node *io_list)
{
	int	i;

	i = 0;
	while (io_list)
	{
		if (io_list->type == T_HEREDOC)
			i++;
		io_list = io_list->next;
	}
	return (i);
}

int	heredoc_warning(char *line, char *delimiter)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document delimited by " \
			"end-of-file (wanted `", 2);
		ft_putstr_fd(delimiter, 2);
		ft_putstr_fd("')\n", 2);
		return (1);
	}
	return (0);
}

/* Reads heredoc input and writes to heredoc pipe */
void	child_heredoc(t_minishell *shell, t_heredoc *node, char *line)
{
	close(node->pipefd[0]);
	while (1)
	{
		line = readline("> ");
		if (heredoc_warning(line, node->delimiter))
			break ;
		if (!ft_strncmp(line, node->delimiter, ft_strlen(line)) \
			&& (ft_strlen(line) == ft_strlen(node->delimiter)))
		{
			free(line);
			break ;
		}
		if (node->node->is_heredoc == 1)
		{
			ft_putstr_fd(line, node->pipefd[1]);
			ft_putstr_fd("\n", node->pipefd[1]);
		}
		free(line);
	}
	close(node->pipefd[1]);
	free_data_and_exit(shell);
}

void	parent_heredoc(t_minishell *shell, int pid, t_heredoc *node)
{
	waitpid(pid, &(shell->exit_status), 0);
	if (ft_exit_status(shell) == SIGINT)
		set_heredoc_sigint(shell);
	close(node->pipefd[1]);
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
	while (node && !shell->heredoc_sigint)
	{
		if (pipe(node->pipefd) == -1)
			return (print_str_err(PIPE_ERR, \
				"error: pipe() failed\n", shell), -1);
		pid = fork();
		if (pid == -1)
			return (print_str_err(FORK_ERR, \
				"error: fork() failed\n", shell), -1);
		heredoc_signal_handler(pid, shell);
		if (!pid)
			child_heredoc(shell, node, line);
		else
			parent_heredoc(shell, pid, node);
		if (node->node->is_heredoc > 1)
			node->node->is_heredoc--;
		node = node->next;
	}
	return (0);
}
