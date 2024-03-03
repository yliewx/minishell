/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:30:02 by agan              #+#    #+#             */
/*   Updated: 2024/02/08 15:30:03 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_handler(int *pipefd, t_minishell *minishell)
{
	if (pipe(pipefd) == -1)
		return (print_str_err(PIPE_ERR, "error: pipe() "\
			"failed\n", minishell), -1);
	return (0);
}

int	fork_handler(int *pid, t_minishell *minishell)
{
	*pid = fork();
	if (*pid == -1)
		return (print_str_err(FORK_ERR, "error: "\
			"fork() failed\n", minishell), -1);
	return (0);
}

/* Dup2 handler - Redirects old fd to new fd */
int	ft_dup(t_minishell *minishell, int oldfd, int newfd)
{
	int	res;

	res = dup2(oldfd, newfd);
	if (res == -1)
		print_str_err(DUP2_ERR, NULL, minishell);
	return (res);
}
