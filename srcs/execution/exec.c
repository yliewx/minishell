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

int binop_next_checker(t_token_type type)
{
    if (type == T_AND || type == T_OR || type == T_PIPE)
        return (1);
    return (0);
}

int redir_handler(t_node *node, int oldfd, int newfd, int pid)
{
    t_io_node *io_list;

    io_list = node->io_list;
    if (pid == 0 || /*builtin boolean checker*/)
    {
        if (node->next_binop == T_PIPE)
            ft_dup(node->minishell, pipefd[1], STDOUT_FILENO);
        while (io_list)
        {
            if (open_handler(node->minishell, io_list, &fd) == -1)
                return ;
            if (io_list->type == T_REDIR_L)
                ft_dup(node->minishell, fd, STDIN_FILENO);
            else if (io_list->type == T_REDIR_R)
                ft_dup(node->minishell, fd, STDOUT_FILENO);
            else if (io_list->type == T_APPEND)
                ft_dup(node->minishell, fd, STDOUT_FILENO);
            else if (io_list->type == T_HEREDOC)
                ft_dup(node->minishell, node->minishell->here_doc[0], STDIN_FILENO);
            io_list = io_list->next;
        }
    }
}

// Function to check for echo, env, pwd
void exec_command(t_node *node, t_minishell *minishell)
{
    int pid;
    int pipefd[2];
    int builtin_type;

    builtin_type = -1;
    get_expanded_arg(node);
    builtin_type = check_builtin(node);
    if (builtin_type == CMD_SIMPLE || builtin_type == CMD_ECHO || \
        builtin_type == CMD_ENV || builtin_type == CMD_PWD)
    {
        if (node->next_binop == T_PIPE)
            pipe(fd);
        pid = fork();
    }
    if (builtin_type != CMD_SIMPLE)
    {
        exec_builtin(node, builtin_type);
    }
    else
    {
        exec_simple_cmd(node, node->expanded_arg, minishell);
    }
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
    if (is_binop_node(ast))
    {
        traverse_tree(ast->left, minishell);
        if (!(WIFEXITED(minishell->exit_status) && ast->next_binop == T_AND) \
            || (WIFEXITED(minishell->exit_status) && ast->next_binop == T_OR) \
            || ast->next_binop == T_PIPE)
                traverse_tree(ast->right, minishell);
    }
    else
        exec_command(ast, minishell);
    return (ast);
}

t_node *ft_exec(t_minishell *minishell)
{
    //if (minishell->here == 1)
    //    continue;
    traverse_tree(minishell->ast, minishell);
    return (minishell->ast);
}