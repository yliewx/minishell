/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:33:08 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 17:33:15 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to print current working directory */
int	ft_pwd(t_minishell *minishell)
{
	int	i;

	i = search_envp_index(minishell->envp, "PWD", 3);
	if (i == -1)
		return (set_exit_success(minishell));
	printf("%s\n", minishell->envp[i] + 4);
	return (set_exit_success(minishell));
}
