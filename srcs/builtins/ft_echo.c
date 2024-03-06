/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:30:05 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 17:31:35 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	flag_checker(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (false);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	flag_counter(t_node *node)
{
	int	i;
	int	count;

	count = 0;
	i = 1;
	while (node->expanded_arg[i])
	{
		if (!flag_checker(node->expanded_arg[i]))
			break ;
		count++;
		i++;
	}
	return (count);
}

/* Function to display a line of text
- Omits newline character if the -n option is present */
int	ft_echo(t_node *node)
{
	int		flag;
	int		i;

	flag = flag_counter(node);
	i = flag + 1;
	while (node->expanded_arg[i])
	{
		if (ft_strlen(node->expanded_arg[i]) > 0)
		{
			printf("%s", node->expanded_arg[i]);
			if (node->expanded_arg[i + 1])
				printf(" ");
		}
		i++;
	}
	if (!flag)
		printf("\n");
	return (set_exit_success(node->minishell));
}
