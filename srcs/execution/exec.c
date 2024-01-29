/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:56:43 by yliew             #+#    #+#             */
/*   Updated: 2024/01/29 11:24:05 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Exec_simple_cmd
    // Split and expand cmd
    // Fork
    // Exec

// Heredoc -> send input to pipe

// Is binop for ast
int is_binop_node(t_node *node)
{
    if (node->type == T_AND || node->type == T_OR || node->type == T_PIPE)
        return (1);
    return (0);
}

// RECURSIVE - traverse_tree
    // Is there heredoc?
    // When it finds a binop
        // traverse_tree left
        // (Condition to check binop)
            // traverse_tree right
    // When simple cmd found -> 
        // Exec and set status

t_node *traverse_tree(t_node *ast, t_minishell *minishell)
{
    if (minishell->heredoc == 1)
        // Run heredoc
        continue;
    if (is_binop_node(ast))
    {
        traverse_tree(ast->left);
        // Check condition
            // traverse_tree(ast->right);
    }
    // split
    ast->expanded_arg = ft_split_argv(ast->value);
    // expand expanded_arg
    if (is_builtin())
    {
        // Exec builtin
    }
    else if (is_simple_cmd())
    {
        // Exec simple cmd
    }
}