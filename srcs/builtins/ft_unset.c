/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:33:18 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 17:33:25 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_data *data, t_command *current)
{
	char	*var_name;
	char	*temp;
	int		i;

	if (!current->argv[1])
		return (1);
	i = 1;
	while (current->argv[i])
	{
		remove_quotes(&current->argv[i]);
		temp = extract_var_name(current->argv[i]);
		var_name = ft_strjoin(temp, "=");
		free(temp);
		update_envp(data, var_name, current->argv[i], "unset");
		free(var_name);
		i++;
	}
	return (1);
}
