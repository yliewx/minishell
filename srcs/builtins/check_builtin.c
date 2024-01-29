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

int	check_builtin(t_minishell *minishell, t_node *node)
{
	if (ft_strncmp(node->expanded_arg[0], "echo", 5) == 0)
		return (ft_echo(node));
	else if (ft_strncmp(node->expanded_arg[0], "cd", 3) == 0)
		return (ft_cd(minishell, node));
	else if (ft_strncmp(node->expanded_arg[0], "pwd", 4) == 0)
		return (ft_pwd(minishell));
	else if (ft_strncmp(node->expanded_arg[0], "export", 7) == 0)
		return (ft_export(minishell, node));
	else if (ft_strncmp(node->expanded_arg[0], "unset", 6) == 0)
		return (ft_unset(minishell, node));
	else if (ft_strncmp(node->expanded_arg[0], "env", 4) == 0)
		return (ft_env(minishell));
	else if (ft_strncmp(node->expanded_arg[0], "exit", 5) == 0)
		return (ft_exit(minishell));
	else
		return (0);
}