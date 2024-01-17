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

int	ft_echo(t_command *current)
{
	int	i;

	i = 1;
	if (!current->argv[i])
		printf("\n");
	while (current->argv[i])
	{
		printf("%s", current->argv[i]);
		i++;
	}
	if (current->argv[1] && ft_strncmp(current->argv[1], "-n", 3) == 0)
		return (1);
	printf("\n");
	return (1);
}
