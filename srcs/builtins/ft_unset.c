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

static int	check_valid_arg(char *arg, char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (unset_error(arg, UNSET_PARAM));
		i++;
	}
	return (1);
}

int	ft_unset(t_data *data, t_command *current)
{
	char	*var_name;
	int		i;

	if (!current->argv[1])
		return (1);
	i = 1;
	while (current->argv[i])
	{
		remove_quotes(&current->argv[i]);
		var_name = extract_var_name(current->argv[i]);
		if (check_valid_arg(current->argv[i], var_name))
			update_envp(data, var_name, current->argv[i], "unset");
		free(var_name);
		i++;
	}
	return (1);
}