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

/*possible cases to handle:
- heredoc interruption?
- sigint when command is in the middle of executing?*/

t_signal g_signal =
{
	false, false, false,
};

// Re-initialize minishell
void	sigint_handler(int signum)
{
	(void)signum;
	if (g_signal.in_heredoc)
	{
		g_signal.sigint = true;
		printf("\n");
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	g_signal.sigint = false;
	g_signal.in_heredoc = false;
	g_signal.in_fork_cmd = false;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
