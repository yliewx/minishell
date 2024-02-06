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

void print_error(t_minishell *minishell, char c)
{
    ft_putstr_fd("minishell: ", 2);
    if (minishell->minishell_err == SYNTAX_ERR)
    {
        ft_putstr_fd("syntax error near unexpected token `", 2);
        ft_putstr_fd(&c, 2);
        ft_putstr_fd("'\n", 2);
    }
    else if (minishell->minishell_err == MEM_ERR)
        ft_putstr_fd("error allocating memory\n", 2);
}