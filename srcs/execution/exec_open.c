/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:24:43 by agan              #+#    #+#             */
/*   Updated: 2024/02/08 13:24:46 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file_checker(t_node *node, t_minishell *minishell, int pid)
{
	t_io_node	*io_list;
	int			res;

	res = 0;
	io_list = node->io_list;
	if (pid != 0)
	{
		while (io_list)
		{
			if (io_list->type == T_REDIR_R)
			{
				res = access(io_list->expanded_arg, F_OK);
				if (!res)
					return (set_exit_error(minishell, OPEN_ERR, 1));
				res = access(io_list->expanded_arg, R_OK);
				if (!res)
					return (set_exit_error(minishell, PERM_ERR, 1));
			}
			io_list = io_list->next;
		}
	}
	return (res);
}

/* Opens file with permissions */
int	open_handler(t_minishell *minishell, t_io_node *io_node, int *fd)
{
	if (io_node->type == T_APPEND)
		*fd = open(io_node->expanded_arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (io_node->type == T_REDIR_L)
		*fd = open(io_node->expanded_arg, O_RDONLY);
	else if (io_node->type == T_REDIR_R)
		*fd = open(io_node->expanded_arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (io_node->type == T_HEREDOC)
		return (0);
	if (*fd == -1)
		print_str_err(OPEN_ERR, io_node->expanded_arg, minishell);
	return (*fd);
}
