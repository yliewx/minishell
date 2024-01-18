/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:15:28 by yliew             #+#    #+#             */
/*   Updated: 2024/01/12 18:15:37 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
{
	int	i;

	free(data->command_list->flags);
	free(data->command_list->arg);
	free(data->command_list);
	i = 0;
	while (data->envp[i])
		free(data->envp[i++]);
	free(data->envp);
}

