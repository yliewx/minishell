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

int	ft_env(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->envp[i])
	{
		printf("%s\n", minishell->envp[i]);
		i++;
	}
	return (minishell->exit_status = 0, 0);
}
