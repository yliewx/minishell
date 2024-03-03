/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:15:28 by yliew             #+#    #+#             */
/*   Updated: 2024/01/12 18:15:37 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arrays(char ***array)
{
	int	i;

	i = 0;
	if (!array | !*array)
		return ;
	while ((*array)[i])
		free((*array)[i++]);
	free(*array);
}

void	free_data(t_minishell *minishell)
{
	free_ast(&minishell->ast);
	free_heredoc(&minishell->heredoc_list);
	ft_free_token_list(&minishell->tokens);
}

void	free_heredoc(t_heredoc **lst)
{
	t_heredoc	*tmp;
	t_heredoc	*next;

	tmp = *lst;
	if (!tmp)
		return ;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->delimiter)
			free(tmp->delimiter);
		free(tmp);
		tmp = next;
	}
	*lst = NULL;
}

void	free_data_and_exit(t_minishell *minishell)
{
	free_data(minishell);
	free_arrays(&minishell->envp);
	free_arrays(&minishell->env_path);
	if (minishell->prompt)
		free(minishell->prompt);
	rl_clear_history();
	exit(minishell->exit_status);
}

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
