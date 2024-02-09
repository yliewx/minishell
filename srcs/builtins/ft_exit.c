/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:32:42 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 17:32:50 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_numeric(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

//add in proper free_minishell function after the structs are finalised
int	ft_exit(t_minishell *minishell, t_node *node)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	while (node->expanded_arg[i])
		i++;
	if (i > 2)
		return (exit_error(ARG_COUNT_ERR, NULL, minishell));
	if (i == 2)
	{
		remove_quotes(&node->expanded_arg[1]);
		if (!is_numeric(node->expanded_arg[1]))
			return (exit_error(PARAM_ERR, node->expanded_arg[1], minishell));
		exit_code = ft_atoi(node->expanded_arg[1]);
	}
	printf("exit\n");
	free_data_and_exit(minishell);
	return (exit(exit_code), 0);
}
