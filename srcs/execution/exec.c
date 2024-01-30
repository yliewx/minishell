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

// Function to check for echo, env, pwd

void exec_commands(t_node *node, t_token_type parent_type)
{
    int pid;
    int pipefd[2];
    char *command_path;

    get_expanded_arg(node);
    if (parent_type == T_PIPE || parent_type == T_AND || parent_type == T_OR)
    {
        if (parent_type == T_PIPE)
            pipe_handler(node, pipefd, parent_type);
        pid = fork();
    }
    if (!check_builtin(minishell, ast) && parent_type)
    
    else (exec_simple_cmd(ast, ast->expanded_arg, parent_type, minishell));
}

// RECURSIVE - traverse_tree
    // Is there heredoc?
    // When it finds a binop
        // traverse_tree left
        // (Condition to check binop)
            // traverse_tree right
    // When simple cmd found -> 
        // Exec and set status

t_node *traverse_tree(t_node *ast, t_token_type parent_type, t_minishell *minishell)
{
    if (is_binop_node(ast))
    {
        traverse_tree(ast->left, parent_type, minishell);
        // Check condition
        //if (WIFEXITED(minishell->status))
        traverse_tree(ast->right, parent_type, minishell);
    }
    else
        exec_command(ast, parent_type);
    return (ast);
}

t_node *ft_exec(t_minishell *minishell)
{
    //if (minishell->here == 1)
    //    continue;
    traverse_tree(minishell->ast, minishell->ast->type, minishell);
    return (minishell->ast);
}