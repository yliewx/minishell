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

bool	check_echo_option(t_node *node)
{
	if (!node->expanded_arg[1])
		return (false);
	return (ft_strncmp(node->expanded_arg[1], "-n", 3) == 0);
}

/* Function to display a line of text
- Omits newline character if the -n option is present */
int	ft_echo(t_node *node)
{
	bool	omit_newline;
	int		i;

	i = 1;
	omit_newline = check_echo_option(node);
	if (omit_newline)
		i++;
	if (node->expanded_arg[1])
	{
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
	}
	if (!omit_newline)
		printf("\n");
	return (set_exit_success(node->minishell));
}
