/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:51:03 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 16:51:04 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	array_dup(t_data *data, char **envp)
{
	int	i;
	int	size;

	size = 0;
	while (envp[size])
		size++;
	data->envp = malloc((size + 1) * sizeof(char*));
	i = 0;
	while (i < size)
	{
		data->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	data->envp[i] = NULL;
}
