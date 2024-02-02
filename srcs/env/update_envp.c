/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:07:29 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 18:07:35 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	resize_envp(t_minishell *minishell, int size, int remove_index)
{
	char	**old_envp;
	int	i;
	int	j;

	old_envp = minishell->envp;
	minishell->envp_size = size;
	minishell->envp = malloc((minishell->envp_size + 1) * sizeof(char*));
	i = -1;
	j = 0;
	if (remove_index >= 0)
	{
		while (++i < size)
		{
			if (j == remove_index)
				j++;
			minishell->envp[i] = old_envp[j++];
		}
		free(old_envp[remove_index]);
	}
	else
	{
		while (++i < size - 1)
			minishell->envp[i] = old_envp[i];
	}
	minishell->envp[i] = NULL;
	free(old_envp);
	return (i);
}

void	update_envp(t_minishell *minishell, char *var, char *value, char *command)
{
	int	i;

	i = search_envp_index(minishell->envp, var, ft_strlen(var));
	if (i >= 0)
	{
		if (ft_strncmp(command, "unset", 6) == 0)
			resize_envp(minishell, minishell->envp_size - 1, i);
		else
		{
			free(minishell->envp[i]);
			minishell->envp[i] = ft_strdup(value);
		}
	}
	else
	{
		if (ft_strncmp(command, "export", 7) == 0)
		{
			i = resize_envp(minishell, minishell->envp_size + 1, -1);
			minishell->envp[i] = ft_strdup(value);
			minishell->envp[i + 1] = NULL;
		}
	}
}
