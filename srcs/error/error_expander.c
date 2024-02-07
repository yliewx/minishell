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
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
	return (set_exit_error(minishell, error, EXIT_FAILURE));
}

bool is_ambiguous_redir(int io_type, t_entry **match_list)
{
	t_entry *temp;

	if (io_type == T_REDIR_L || io_type == T_REDIR_R || io_type == T_APPEND)
	{
		temp = *match_list;
		while (temp->next)
			temp = temp->next;
		if (temp != *match_list)
			return (free_match_list(match_list), true);
	}
	return (false);
}
