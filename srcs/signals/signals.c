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

/* Define global variable to store signal information
- Is separated from minishell data struct */
t_signal	g_signal = {
	0, false, false, false,
};

/* Function for handling response to SIGINT
- Sets global signum to SIGINT
- If SIGINT is received when executing heredoc:
	- Child process exits with SIGINT
	- Parent process sets sigint_heredoc to true
- Else if the parent resets readline display only if there is no child */
void	sigint_handler(int signum)
{
	g_signal.signum = signum;
	if (g_signal.in_heredoc)
	{
		if (!g_signal.is_forked_parent)
		{
			printf("\n");
			exit(SIGINT);
		}
		else
			g_signal.sigint_heredoc = true;
	}
	else
	{
		printf("\n");
		if (!g_signal.is_forked_parent)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

/* Function to init/reset signal information before the ft_minishell loop
- Calls sigint_handler when SIGINT is received
- Ignores SIGQUIT */
void	init_signals(void)
{
	g_signal.signum = 0;
	g_signal.sigint_heredoc = false;
	g_signal.in_heredoc = false;
	g_signal.is_forked_parent = false;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
