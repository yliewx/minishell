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

// Look into output not consistently piped 
int redir_handler(t_node *node, int pid, int *pipefd)
{
    t_io_node *io_list;
    int fd;

    io_list = node->io_list;
    //printf("node %s entered redir_handler\n", node->value);
    if (pid == 0 || !is_fork_cmd(check_builtin(node)))
    {
        if (node->next_binop == T_PIPE)
        {
            close(pipefd[0]);
            ft_dup(node->minishell, pipefd[1], STDOUT_FILENO);
        }
        while (io_list)
        {
            if (open_handler(node->minishell, io_list, &fd) == -1)
                return (-1);
            if (io_list->type == T_REDIR_L)
            {
                //printf("redir input to %s\n", io_list->value);
                ft_dup(node->minishell, fd, STDIN_FILENO);
            }
            else if (io_list->type == T_REDIR_R)
            {
                //printf("redir output to %s\n", io_list->value);
                ft_dup(node->minishell, fd, STDOUT_FILENO);
            }
            else if (io_list->type == T_APPEND)
                ft_dup(node->minishell, fd, STDOUT_FILENO);
            else if (io_list->type == T_HEREDOC)
                ft_dup(node->minishell, node->minishell->here_doc[0], STDIN_FILENO);
            io_list = io_list->next;
        }
    }
    else
    {
        if (node->next_binop == T_PIPE)
        {
            close(pipefd[1]);
            ft_dup(node->minishell, pipefd[0], STDIN_FILENO);
        }
    }
    return (0);
}

// Function to check for echo, env, pwd
void exec_command(t_node *node, t_minishell *minishell)
{
    int pid;
    int pipefd[2];
    int builtin_type;

    pid = -1;
    builtin_type = -1;
    get_expanded_arg(node);
    builtin_type = check_builtin(node);
    if (is_fork_cmd(builtin_type))
    {
        if (node->next_binop == T_PIPE)
            pipe(pipefd);
        pid = fork();
    }
    if (redir_handler(node, pid, pipefd) == -1)
        return ;
    if (builtin_type != CMD_SIMPLE)
    {
        exec_builtin(node, builtin_type, pid);
    }
    else
    {
        exec_simple_cmd(node, node->expanded_arg, minishell, pid);
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
        if ((WIFEXITED(minishell->exit_status) && ast->type == T_AND) \
            || (!WIFEXITED(minishell->exit_status) && ast->type == T_OR)
            || ast->type == T_PIPE)
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