/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:33:08 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 17:33:15 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_minishell *minishell)
{
	int	i;

	i = search_envp_index(minishell->envp, "PWD", 3);
	printf("%s\n", minishell->envp[i] + 4);
	return (0);
}
