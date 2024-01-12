/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:05:30 by yliew             #+#    #+#             */
/*   Updated: 2023/10/16 14:51:35 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*COPIED FROM PIPEX - TO BE UPDATED*/

#include "pipex_bonus.h"

void	perror_exit(char *message, int exit_code)
{
	perror(message);
	exit(exit_code);
}

void	check_exit_status(int child_exit_code)
{
	int	status;

	if (WIFEXITED(child_exit_code))
	{
		status = WEXITSTATUS(child_exit_code);
		if (status != 0)
			exit(status);
	}
}

void	close_pipes(int pipe1, int pipe2)
{
	close(pipe1);
	close(pipe2);
}
