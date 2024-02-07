/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:40:05 by agan              #+#    #+#             */
/*   Updated: 2024/01/29 12:40:09 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Is binop for ast
int is_binop_node(t_node *node)
{
    if (node->type == T_AND || node->type == T_OR || node->type == T_PIPE)
        return (1);
    return (0);
}

int binop_next_checker(t_token_type type)
{
    if (type == T_AND || type == T_OR || type == T_PIPE)
        return (1);
    return (0);
}

int open_handler(t_minishell *minishell, t_io_node *io_node, int *fd)
{
    if (io_node->type == T_APPEND)
        *fd = open(io_node->expanded_arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (io_node->type == T_REDIR_L)
        *fd = open(io_node->expanded_arg, O_RDONLY);
    else if (io_node->type == T_REDIR_R)
        *fd = open(io_node->expanded_arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (io_node->type == T_HEREDOC)
        return (0);
    if (*fd == -1)
	{
		//perror("Error opening file\n");
        ft_putstr_fd("Error opening file\n", 2);
        minishell->minishell_err = OPEN_ERR;
	}
    return (*fd);
}
