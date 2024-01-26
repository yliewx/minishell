/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:51:03 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 16:51:04 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_oldpwd(void)
{
	char	*oldpwd;
	char	*temp;

	temp = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", temp);
	free(temp);
	return (oldpwd);
}

void	array_dup(t_data *data, char **envp)
{
	int	i;

	i = -1;
	data->envp_size = 0;
	while (envp[data->envp_size])
		data->envp_size++;
	if (search_envp_index(envp, "OLDPWD=", 7) == -1)
	{
		data->envp_size++;
		data->envp = malloc((data->envp_size + 1) * sizeof(char*));
		while (++i < data->envp_size - 1)
			data->envp[i] = ft_strdup(envp[i]);
		data->envp[i++] = init_oldpwd();
	}
	else
	{
		data->envp = malloc((data->envp_size + 1) * sizeof(char*));
		while (++i < data->envp_size)
			data->envp[i] = ft_strdup(envp[i]);
	}
	data->envp[i] = NULL;
	sort_envp(data->envp, 0, data->envp_size - 1);
}
