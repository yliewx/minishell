/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_expander.c                                   :+:      :+:    :+:   */
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
	ft_putstr_fd("minishell: ", 2);
	if (error == AMBIG_REDIR_ERR)
	{
		if (arg[0])
			write(2, &arg[0], 1);
		if (arg[1] && arg[1] == '*')
			write(2, &arg[1], 1);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
	return (set_exit_error(minishell, error, EXIT_FAILURE));
}

bool is_ambiguous_redir(t_io_node *io_node)
{
	if (io_node->type == T_REDIR_L || io_node->type == T_REDIR_R
		|| io_node->type == T_APPEND)
	{
		return (ft_strncmp(io_node->value, "* ", 2) == 0
			|| ft_strncmp(io_node->value, ".* ", 3) == 0
			|| ft_strncmp(io_node->value, "*", 2) == 0
			|| ft_strncmp(io_node->value, ".*", 3) == 0);
	}
	return (false);
}
