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

int	ft_echo(t_node *node)
{
	int	i;

	i = 1;
	if (!node->expanded_arg[i])
		printf("\n");
	while (node->expanded_arg[i])
	{
		remove_quotes(&node->expanded_arg[i]);
		if (ft_strlen(node->expanded_arg[i]) > 0)
		{
			printf("%s", node->expanded_arg[i]);
			if (node->expanded_arg[i + 1])
				printf(" ");
		}
		i++;
	}
	if (node->expanded_arg[1] && ft_strncmp(node->expanded_arg[1], "-n", 3) == 0)
		return (0);
	printf("\n");
	return (0);
}