/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:53:58 by yliew             #+#    #+#             */
/*   Updated: 2024/02/05 14:54:03 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_minishell *minishell, char **envp)
{
	minishell->envp = NULL;
	minishell->env_path = NULL;
	minishell->envp_size = 0;
	if (envp)
	{
		envp_dup(minishell, envp);
		minishell->env_path = get_env_path(envp);
	}
}
