/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:56:00 by agan              #+#    #+#             */
/*   Updated: 2024/02/01 15:56:01 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Redirect child process
If pipe -> read dup write pipe to stdout
Set redirect from io_list nodes */
int	child_redirect(t_node *node, int *fd, t_io_node *io_list, int *pipefd)
{
	if (node->next_binop == T_PIPE)
	{
		close(pipefd[0]);
		ft_dup(node->minishell, pipefd[1], STDOUT_FILENO);
	}
	while (io_list)
	{
		if (open_handler(node->minishell, io_list, fd) == -1)
			return (-1);
		if (io_list->type == T_REDIR_L)
			ft_dup(node->minishell, *fd, STDIN_FILENO);
		else if (io_list->type == T_REDIR_R)
			ft_dup(node->minishell, *fd, STDOUT_FILENO);
		else if (io_list->type == T_APPEND)
			ft_dup(node->minishell, *fd, STDOUT_FILENO);
		else if (io_list->type == T_HEREDOC)
		{
			close(node->minishell->heredoc_list->pipefd[1]);
			ft_dup(node->minishell, node->minishell->heredoc_list->pipefd[0], \
				STDIN_FILENO);
		}
		io_list = io_list->next;
	}
	return (0);
}

/* Function to set redirects
- If forked, run child_redirect for child process
- For parent/main, redirect pipes and heredoc */
int	redir_handler(t_node *node, int pid, int *pipefd)
{
	t_io_node	*io_list;
	int			fd;

	fd = -1;
	io_list = node->io_list;
	if (pid == 0 || !is_fork_cmd(node, check_builtin(node)))
	{
		if (child_redirect(node, &fd, io_list, pipefd) == -1)
			return (-1);
	}
	else
	{
		if (node->next_binop == T_PIPE)
		{
			close(pipefd[1]);
			ft_dup(node->minishell, pipefd[0], STDIN_FILENO);
		}
		if (node->is_heredoc == 1)
		{
			close(node->minishell->heredoc_list->pipefd[1]);
			close(node->minishell->heredoc_list->pipefd[0]);
			remove_heredoc_node(&(node->minishell->heredoc_list));
		}
	}
	return (0);
}
