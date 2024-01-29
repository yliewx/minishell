/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:15:28 by yliew             #+#    #+#             */
/*   Updated: 2024/01/12 18:15:37 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_minishell *minishell)
{
	int	i;

	/*free(minishell->command_list->flags);
	free(minishell->command_list->arg);
	free(minishell->command_list);*/
	i = 0;
	while (minishell->envp[i])
		free(minishell->envp[i++]);
	free(minishell->envp);
}
