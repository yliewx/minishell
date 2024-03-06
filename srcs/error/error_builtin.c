/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:44:31 by yliew             #+#    #+#             */
/*   Updated: 2024/01/17 18:44:37 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error(int error, char *arg, t_minishell *minishell)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (error == ARG_COUNT_ERR)
		ft_putstr_fd("too many arguments\n", 2);
	else if (error == NODIR_ERR)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (error == NOT_SET_ERR)
		ft_putstr_fd("HOME not set\n", 2);
	return (set_exit_error(minishell, error, EXIT_FAILURE));
}

int	exit_error(int error, char *arg, t_minishell *minishell)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (error == ARG_COUNT_ERR)
		ft_putstr_fd("too many arguments\n", 2);
	else if (error == PARAM_ERR)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (set_exit_error(minishell, error, 2));
	}
	return (set_exit_error(minishell, error, EXIT_FAILURE));
}

int	export_error(int error, char *arg, t_minishell *minishell)
{
	ft_putstr_fd("minishell: export: ", 2);
	if (error == EXPORT_ID_ERR)
	{
		ft_putstr_fd("`", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else if (error == EXPORT_OPTION_ERR)
	{
		ft_putstr_fd("-", 2);
		write(2, &arg[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		ft_putstr_fd("export: usage: export [name[=value] ...]\n", 2);
	}
	return (set_exit_error(minishell, error, EXIT_FAILURE));
}

int	unset_error(int error, char *arg, t_minishell *minishell)
{
	if (error == PARAM_ERR)
	{
		ft_putstr_fd("minishell: unset: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": invalid parameter name\n", 2);
	}
	return (set_exit_error(minishell, error, EXIT_FAILURE));
}
