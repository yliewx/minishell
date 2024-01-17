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

	old_envp = data->envp;
	data->envp_size = size;
	data->envp = malloc((size + 1) * sizeof(char*));
	i = -1;
	if (remove_index >= 0)
	{
		while (++i < size)
		{
			if (i == remove_index)
				i++;
			data->envp[i] = old_envp[i];
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

char	*extract_var_name(char *arg)
{
	char	*var_name;
	int		i;

	i = 0;
	if (!ft_strchr(arg, '='))
		return (arg);
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
		i++;
	var_name = ft_substr(arg, 0, i);
	return (var_name);
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
