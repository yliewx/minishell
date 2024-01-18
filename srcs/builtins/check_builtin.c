/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:15:42 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 17:15:50 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(t_data *data, t_command *current)
{
	if (current->argv[1])
		check_expand_variables(current, current->argv[1]);
	if (data && ft_strncmp(current->argv[0], "echo", 5) == 0)
		return (ft_echo(current));
	else if (ft_strncmp(current->argv[0], "cd", 3) == 0)
		return (ft_cd(data));
	else if (ft_strncmp(current->argv[0], "pwd", 4) == 0)
		return (ft_pwd(data));
	else if (ft_strncmp(current->argv[0], "export", 7) == 0)
		return (ft_export(data, current));
	else if (ft_strncmp(current->argv[0], "unset", 6) == 0)
		return (ft_unset(data, current));
	else if (ft_strncmp(current->argv[0], "env", 4) == 0)
		return (ft_env(data));
	else if (ft_strncmp(current->argv[0], "exit", 5) == 0)
		return (ft_exit(data, current));
	else
		return (0);
}
