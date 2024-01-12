/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:29:06 by yliew             #+#    #+#             */
/*   Updated: 2023/10/18 14:40:12 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*COPIED FROM PIPEX - TO BE UPDATED*/

#include "pipex_bonus.h"

/*child process:
- write user input to the write end of the pipe (pipefd[1])
- exit when the limiter is encountered on a line by itself
  (continue reading if there are still characters before/after the limiter)*/
void	write_heredoc(char *limiter, int *pipefd)
{
	char	*current_line;

	close(pipefd[0]);
	while (1)
	{
		ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
		current_line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(current_line, limiter,
				ft_strlen(current_line) - 1) == 0
			&& ft_strlen(current_line) - 1 == ft_strlen(limiter))
		{
			free(current_line);
			close(pipefd[1]);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(current_line, pipefd[1]);
		free(current_line);
	}
}

/*parent process:
- redirect standard input to the read end of the pipe (pipefd[0])
- pass the read end (pipefd[0]) to the process_handler as input_fd
- next child will read from that input_fd to execute commands*/
void	redirect_heredoc(int *pipefd)
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		perror_exit("Stdin redirection failed", EXIT_FAILURE);
}

int	heredoc_handler(char *limiter)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		perror_exit("Pipe failed", EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		perror_exit("Fork failed", EXIT_FAILURE);
	if (pid == 0)
		write_heredoc(limiter, pipefd);
	redirect_heredoc(pipefd);
	waitpid(pid, NULL, 0);
	return (pipefd[0]);
}
