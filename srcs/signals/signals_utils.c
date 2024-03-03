/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:25:45 by yliew             #+#    #+#             */
/*   Updated: 2024/01/24 18:25:51 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Define global variable to store signal number */
int	g_signum = 0;

void	set_g_signum(int signum)
{
	g_signum = signum;
}

void	sigint_write_nl(int signum)
{
	set_g_signum(signum);
	printf("\n");
}

void	sigint_readline(int signum)
{
	sigint_write_nl(signum);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_exit(int signum)
{
	sigint_write_nl(signum);
	exit(SIGINT);
}

void	sigquit_handler(int signum)
{
	set_g_signum(signum);
	printf("Quit\n");
}
