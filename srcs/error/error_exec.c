/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:15:25 by yliew             #+#    #+#             */
/*   Updated: 2024/02/06 13:15:27 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_error(int error, char *arg, t_minishell *minishell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	if (error == CMD_NOT_FOUND_ERR)
		ft_putstr_fd(": command not found\n", 2);
	else if (error == DIR_ERR)
	{
		ft_putstr_fd(": Is a directory\n", 2);
		return (set_exit_error(minishell, error, 126));
	}
	else if (error == FILE_NOT_FOUND_ERR)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (error == PERM_ERR)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		return (set_exit_error(minishell, error, 126));
	}
	return (set_exit_error(minishell, error, 127));
}
