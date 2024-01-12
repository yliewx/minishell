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

void	update_env(t_data *data, char *var, char *value)
{
	char	*temp;
	int	i;

	i = 0;
	while (data->envp[i]
		&& ft_strncmp(data->envp[i], var, ft_strlen(var)) != 0)
		i++;
	free(data->envp[i]);
	temp = ft_strjoin(var, "=");
	data->envp[i] = ft_strjoin(temp, value);
	free(temp);
}
