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
/*
void print_char_err(t_minishell *minishell, char c)
{
    ft_putstr_fd("minishell: ", 2);
    if (minishell->minishell_err == SYNTAX_ERR)
    {
        ft_putstr_fd("syntax error near unexpected token `", 2);
        write(2, &c, 1);
        ft_putstr_fd("'\n", 2);
    }
}

void print_str_err(t_minishell *minishell, char *str)
{
    ft_putstr_fd("minishell: ", 2);
    if (minishell->minishell_err == SYNTAX_ERR)
    {
        ft_putstr_fd("syntax error near unexpected token `", 2);
        ft_putstr_fd(str, 2);        
        ft_putstr_fd("'\n", 2);
    }
    else if (minishell->minishell_err == MEM_ERR)
        ft_putstr_fd("error allocating memory\n", 2);
}
*/
int print_char_err(int error, char c, t_minishell *minishell)
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

int print_str_err(int error, char *str, t_minishell *minishell)
{
    ft_putstr_fd("minishell: ", 2);
    if (error == SYNTAX_ERR)
    {
        ft_putstr_fd("syntax error near unexpected token `", 2);
        ft_putstr_fd(str, 2);        
        ft_putstr_fd("'\n", 2);
    }
    else if (error == MEM_ERR)
        ft_putstr_fd("error allocating memory\n", 2);
    return (set_exit_error(minishell, error, EXIT_FAILURE));
}
