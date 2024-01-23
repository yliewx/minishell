/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:07:29 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 18:07:35 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_envp_index(char **envp, char *var, int len)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	resize_envp(t_data *data, int size, int remove_index)
{
	char	**old_envp;
	int	i;
	int	j;

	old_envp = data->envp;
	data->envp_size = size;
	data->envp = malloc((size + 1) * sizeof(char*));
	i = -1;
	j = 0;
	if (remove_index >= 0)
	{
		while (++i < size)
		{
			if (j == remove_index)
				j++;
			data->envp[i] = old_envp[j++];
		}
		free(old_envp[remove_index]);
	}
	else
	{
		while (++i < size - 1)
			data->envp[i] = old_envp[i];
	}
	data->envp[i] = NULL;
	free(old_envp);
	return (i);
}

void	update_envp(t_data *data, char *var, char *value, char *command)
{
	int	i;

	i = search_envp_index(data->envp, var, ft_strlen(var));
	if (i >= 0)
	{
		if (ft_strncmp(command, "unset", 6) == 0)
			resize_envp(data, data->envp_size - 1, i);
		else
		{
			free(data->envp[i]);
			data->envp[i] = value;
		}
	}
	else
	{
		if (ft_strncmp(command, "export", 7) == 0)
		{
			i = resize_envp(data, data->envp_size + 1, -1);
			data->envp[i] = value;
			data->envp[i + 1] = NULL;
		}
	}
}
