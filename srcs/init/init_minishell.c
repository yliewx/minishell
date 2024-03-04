/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:36:55 by agan              #+#    #+#             */
/*   Updated: 2024/02/05 14:36:56 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reinit(t_minishell *minishell, char *command)
{
	dup2(minishell->old_stdin, STDIN_FILENO);
	free(command);
	free_data(minishell);
	free_arrays(&minishell->env_path);
	minishell->env_path = get_env_path(minishell->envp, minishell);
	if (minishell->prompt)
		free(minishell->prompt);
	init_minishell(minishell, false);
}

void	init_minishell(t_minishell *minishell, bool start)
{
	set_g_signum(0);
	readline_signal_handler();
	if (start)
	{
		minishell->old_stdin = dup(STDIN_FILENO);
		minishell->exit_status = 0;
	}
	minishell->ast = NULL;
	minishell->tokens = NULL;
	minishell->curr_token = NULL;
	minishell->heredoc_list = NULL;
	minishell->heredoc_count = 0;
	minishell->heredoc_sigint = false;
	minishell->minishell_err = 0;
	if (minishell->envp)
		minishell->user = value_in_env(minishell->envp, "USER");
	else
		minishell->user = NULL;
	ft_prompt(minishell);
}
