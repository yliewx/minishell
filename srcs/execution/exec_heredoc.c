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
void	ft_heredoc(char *limiter, int *pipefd)
{
	char	*curr_line;
    char    *line;

	while (1)
	{
		curr_line = readline("heredoc> ");
		if (ft_strncmp(line, limiter,
				ft_strlen(line) - 1) == 0
			&& ft_strlen(line) - 1 == ft_strlen(limiter))
		{
			free(curr_line);
			break ;
		}
		ft_putstr_fd(curr_line, pipefd[1]);
		free(curr_line);
	}
}
