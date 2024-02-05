/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:18:11 by yliew             #+#    #+#             */
/*   Updated: 2024/02/05 15:18:18 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expander_error(int error, char *arg, t_minishell *minishell)
{
	ft_putstr_fd("minishell: ");
	if (error == AMBIG_REDIR_ERR)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ambiguous redirect\n");
	}
	return (set_exit_error(minishell, error, EXIT_FAILURE));
}
