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

/* Function to pipe heredoc input */
int	ft_heredoc(t_heredoc *list, t_minishell *shell)
{
	t_heredoc	*node;
	char		*line;

	node = list;
	g_signal.in_heredoc = true;
	while (node && !g_signal.sigint)
	{
		if (pipe(node->pipefd) == -1)
			return (print_str_err(PIPE_ERR, "error: pipe() failed\n", shell));
		while (1)
		{
			line = readline("> ");
			if (g_signal.sigint || (!ft_strncmp(line, node->delimiter, ft_strlen(line)) \
				&& (ft_strlen(line) == ft_strlen(node->delimiter))))
			{
				free(line);
				break ;
			}
			ft_putstr_fd(line, node->pipefd[1]);
			ft_putstr_fd("\n", node->pipefd[1]);
			free(line);
		}
		node = node->next;
	}
	g_signal.in_heredoc = false;
	return (0);
}
