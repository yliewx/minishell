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
void exec_command(t_node *node, t_token_type parent_type, t_minishell *minishell)
{
    int pid;
    int pipefd[2];
    int builtin_type;

    builtin_type = -1;
    get_expanded_arg(node);
    builtin_type = check_builtin(node);
    if ((parent_type == T_PIPE || parent_type == T_AND || parent_type == T_OR) && \
        builtin_type && (builtin_type == CMD_ECHO || builtin_type == CMD_ENV \
         || builtin_type == CMD_PWD))
    {
        if (parent_type == T_PIPE)
            pipe_handler(node, pipefd, parent_type);
        pid = fork();
    }
    if (builtin_type != CMD_SIMPLE)
    {
        if (pid == 0)
            exec_builtin(node, builtin_type);
    }
    else
        exec_simple_cmd(node, node->expanded_arg, parent_type, minishell);
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
        if ((WIFEXITED(minishell->exit_status) == 0 && parent_type == T_AND) \
            || (WIFEXITED(minishell->exit_status) && parent_type == T_OR))
                traverse_tree(ast->right, parent_type, minishell);
    }
    else
        exec_command(ast, parent_type, minishell);
    return (ast);
}

t_node *ft_exec(t_minishell *minishell)
{
    //if (minishell->here == 1)
    //    continue;
    traverse_tree(minishell->ast, minishell->ast->type, minishell);
    return (minishell->ast);
}