/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:44:31 by yliew             #+#    #+#             */
/*   Updated: 2024/01/17 18:44:37 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_error_exit_status(t_minishell *minishell, int error, int status)
{
	minishell->minishell_err = error;
	minishell->exit_status = status;
}

int	cd_error(int error, char *arg, t_minishell *minishell)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (error == CD_ARG)
		ft_putstr_fd("too many arguments\n", 2);
	else if (error == CD_NODIR)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	set_error_exit_status(minishell, error, 1);
	return (1);
}

int	export_error(int error, char *arg, t_minishell *minishell)
{
	ft_putstr_fd("minishell: export: ", 2);
	if (error == EXPORT_IDENTIFIER)
	{
		ft_putstr_fd("`", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
	}
	else if (error == EXPORT_OPTION)
	{
		ft_putstr_fd("-", 2);
		write(2, &arg[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("export: usage: export [name[=value] ...]\n", 2);
	}
	set_error_exit_status(minishell, error, 1);
	return (1);
}

int	unset_error(int error, char *arg, t_minishell *minishell)
{
	if (error == UNSET_PARAM)
	{
		ft_putstr_fd("minishell: unset: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": invalid parameter name\n", 2);
	}
	set_error_exit_status(minishell, error, 1);
	return (1);
}