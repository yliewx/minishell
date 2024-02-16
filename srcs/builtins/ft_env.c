/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:32:29 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 17:32:36 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to print list of environment variables */
int	ft_env(t_minishell *minishell)
{
	int	i;

	i = 0;
	if (!minishell->envp)
		return (set_exit_success(minishell));
	while (minishell->envp[i])
	{
		printf("%s\n", minishell->envp[i]);
		i++;
	}
	return (set_exit_success(minishell));
}
