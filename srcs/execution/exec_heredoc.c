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

// Heredoc -> send input to pipe
void	ft_heredoc(t_heredoc *list)
{
	t_heredoc *curr_node;
	char	*curr_line;

	curr_node = list;
	if (!curr_node)
		return ;
	while (curr_node)
	{
		pipe(curr_node->pipefd);
		while (1)
		{
			curr_line = readline("> ");
			if (!ft_strncmp(curr_line, curr_node->delimiter, ft_strlen(curr_line)) \
				&& (ft_strlen(curr_line) == ft_strlen(curr_node->delimiter)))
			{
				free(curr_line);
				break ;
			}
			ft_putstr_fd(curr_line, curr_node->pipefd[1]);
			ft_putstr_fd("\n", curr_node->pipefd[1]);
			free(curr_line);
		}
		curr_node = curr_node->next;
	}
}
