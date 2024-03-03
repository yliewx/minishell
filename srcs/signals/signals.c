/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:25:45 by yliew             #+#    #+#             */
/*   Updated: 2024/01/24 18:25:51 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to set sigaction struct values */
void	init_sigaction(struct sigaction *sa, void (*handler)(int), \
	int flag)
{
	sa->sa_handler = handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = flag;
}

/* Function to reset signal handling in interactive mode
- Calls sigint_readline when SIGINT is received
- Ignores SIGQUIT */
void	readline_signal_handler(void)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	init_sigaction(&sa_sigint, sigint_readline, 0);
	init_sigaction(&sa_sigquit, SIG_IGN, 0);
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

void	ignore_signal_handler(void)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	init_sigaction(&sa_sigint, sigint_write_nl, SA_RESTART);
	init_sigaction(&sa_sigquit, SIG_IGN, SA_RESTART);
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

/* Function to set signal handling for heredoc
[SIGINT]
	- Child: Writes "\n" and exits
	- Parent: Ignores SIGINT and restarts waitpid
[SIGQUIT]
	- Both child and parent ignore SIGQUIT */
void	heredoc_signal_handler(int pid)
{
	struct sigaction	sa_sigint;

	if (pid == 0)
		init_sigaction(&sa_sigint, sigint_exit, 0);
	else
		init_sigaction(&sa_sigint, SIG_IGN, SA_RESTART);
	sigaction(SIGINT, &sa_sigint, NULL);
}

/* Function to set signal handling in exec mode
[SIGINT]
	- Child: Default behaviour
	- Parent: Writes "\n" and restarts waitpid
[SIGQUIT]
	- Child: Default behaviour
	- Parent: Writes "Quit\n" and restarts waitpid */
void	exec_signal_handler(int pid)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	if (pid == 0)
	{
		init_sigaction(&sa_sigint, SIG_DFL, 0);
		init_sigaction(&sa_sigquit, SIG_DFL, 0);
	}
	else
	{
		init_sigaction(&sa_sigint, sigint_write_nl, SA_RESTART);
		init_sigaction(&sa_sigquit, sigquit_handler, SA_RESTART);
	}
	sigaction(SIGINT, &sa_sigint, NULL);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}
