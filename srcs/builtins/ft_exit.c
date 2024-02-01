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

//add in proper free_minishell function after the structs are finalised
int	ft_exit(t_minishell *minishell)
{
	printf("exit\n");
	free_data(minishell);
	exit(EXIT_FAILURE);
	return (0);
}
