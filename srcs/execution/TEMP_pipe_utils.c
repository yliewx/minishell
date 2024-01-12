/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:56:24 by yliew             #+#    #+#             */
/*   Updated: 2023/10/18 14:34:01 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*COPIED FROM PIPEX - TO BE UPDATED*/

#include "pipex_bonus.h"

/*child process:
- replace stdin with the read end of the pipe (input_fd)*/
void	read_pipe_handler(int *pipefd, int input_fd)
{
	close(pipefd[0]);
	if (dup2(input_fd, STDIN_FILENO) == -1)
		perror_exit("Stdin redirection failed", EXIT_FAILURE);
}

/*child process:
- replace stdout with the write end of the pipe (pipefd[1])
- if at the last command, replace stdout with outfile*/
void	write_pipe_handler(char **argv, int index, int *pipefd, int *outfile)
{
	if (argv[index + 2] == NULL)
	{
		if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		{
			*outfile = open(argv[index + 1],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else
		{
			*outfile = open(argv[index + 1],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (*outfile == -1)
			perror("Error opening outfile");
		if (dup2(*outfile, STDOUT_FILENO) == -1)
			perror_exit("Outfile redirection failed", EXIT_FAILURE);
	}
	else
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			perror_exit("Stdout redirection failed", EXIT_FAILURE);
	}
}
