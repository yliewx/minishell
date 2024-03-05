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
int	child_redirect(t_node *node, int *fd, t_io_node *io_list)
{
	int	res;

	while (io_list)
	{
		res = -1;
		if (open_handler(node->minishell, io_list, fd) == -1)
			return (-1);
		if (io_list->type == T_REDIR_L)
			res = ft_dup(node->minishell, *fd, STDIN_FILENO);
		else if (io_list->type == T_REDIR_R)
			res = ft_dup(node->minishell, *fd, STDOUT_FILENO);
		else if (io_list->type == T_APPEND)
			res = ft_dup(node->minishell, *fd, STDOUT_FILENO);
		else if (io_list->type == T_HEREDOC)
		{
			ft_dup(node->minishell, node->minishell->heredoc_list->pipefd[0], \
				STDIN_FILENO);
			close(node->minishell->heredoc_list->pipefd[0]);
			remove_heredoc_node(&(node->minishell->heredoc_list));
		}
		if (io_list->type != T_HEREDOC && res != -1)
			close(*fd);
		io_list = io_list->next;
	}
	return (0);
}

void	parent_redirect(t_node *node)
{
	int	count;

	if (node->is_heredoc == 1)
	{
		count = heredoc_count(node->io_list);
		while (count-- > 0)
		{
			close(node->minishell->heredoc_list->pipefd[0]);
			remove_heredoc_node(&(node->minishell->heredoc_list));
		}
	}
}

/* Function to set redirects
- If forked, run child_redirect for child process
- For parent/main, redirect pipes and heredoc */
int	redir_handler(t_node *node, int pid)
{
	t_io_node	*io_list;
	int			fd;

	fd = -1;
	io_list = node->io_list;
	if (pid == 0)
	{
		if (child_redirect(node, &fd, io_list) == -1)
			return (-1);
	}
	else
		parent_redirect(node);
	return (0);
}
