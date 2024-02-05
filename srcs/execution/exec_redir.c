/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:56:00 by agan              #+#    #+#             */
/*   Updated: 2024/02/01 15:56:01 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Dup2 handler -> open infile
    // handle if infile does not exists
    // Create if outfile does not exist
    // If append > O_APPEND
    // If heredoc > refer to here_doc pipe
int ft_dup(t_minishell *minishell, int oldfd, int newfd)
{
    int res;

    res = dup2(oldfd, newfd);
    if (res == -1)
	{
		perror("Error duping\n");
        minishell->minishell_err = DUP2_ERR;
	}
    return (res);
}

// Function to remove node of heredoc_list
void remove_heredoc_node(t_heredoc **list)
{
    t_heredoc *to_free;

    to_free = *list;
    if (to_free)
    {
        *list = (*list)->next;
        free(to_free->delimiter);
        free(to_free);
    }
}

// Look into output not consistently piped 
int redir_handler(t_node *node, int pid, int *pipefd)
{
    t_io_node *io_list;
    int fd;

    fd = -1;
    io_list = node->io_list;
    //printf("node %s entered redir_handler, next binop type is %i\n", node->value, node->next_binop);
    if (pid == 0 || !is_fork_cmd(node, check_builtin(node)))
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
            {
                close(node->minishell->heredoc_list->pipefd[1]);
                ft_dup(node->minishell, node->minishell->heredoc_list->pipefd[0], STDIN_FILENO);
            }
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
        if (node->is_heredoc == 1)
        {
            close(node->minishell->heredoc_list->pipefd[1]);
            close(node->minishell->heredoc_list->pipefd[0]);
            remove_heredoc_node(&(node->minishell->heredoc_list));
        }
    }
    return (0);
}
