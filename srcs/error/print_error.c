/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:28:40 by agan              #+#    #+#             */
/*   Updated: 2024/02/06 10:28:41 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_char_err(int error, char c, t_minishell *minishell)
{
	ft_putstr_fd("minishell: ", 2);
	if (error == SYNTAX_ERR)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		write(2, &c, 1);
		ft_putstr_fd("'\n", 2);
	}
	return (set_exit_error(minishell, error, EXIT_FAILURE));
}

void print_err_helper(int error, char *str)
{
	if (error == OPEN_ERR)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
	}
	else if (error == PERM_ERR)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("Permission denied\n", 2);
	}
	else if (error == SYNTAX_ERR)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
	}
}

int	print_str_err(int error, char *str, t_minishell *minishell)
{
	ft_putstr_fd("minishell: ", 2);
	if (error == SYNTAX_ERR)
		print_err_helper(SYNTAX_ERR, str);
	else if (error == DUP2_ERR)
		ft_putstr_fd("error: dup2 failed\n", 2);
	else if (error == MEM_ERR)
		ft_putstr_fd("error: memory allocation failed\n", 2);
	else if (error == OPEN_ERR)
		print_err_helper(OPEN_ERR, str);
	else if (error == PERM_ERR)
		print_err_helper(PERM_ERR, str);
	else if (error == PIPE_ERR || error == FORK_ERR)
		ft_putstr_fd(str, 2);
	return (set_exit_error(minishell, error, EXIT_FAILURE));
}
