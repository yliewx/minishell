/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:17:28 by agan              #+#    #+#             */
/*   Updated: 2024/02/22 15:17:29 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Redir for pipe 
Left node - 0 
Right node - 1
Main - 2 */
void	redir_pipe(int *pipefd, t_minishell *minishell, int node, t_node *ast)
{
	if (node == LEFT_NODE)
	{
		close(pipefd[0]);
		ft_dup(minishell, pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		traverse_tree(ast->left, minishell, ast);
	}
	else if (node == RIGHT_NODE)
	{
		close(pipefd[1]);
		ft_dup(minishell, pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		traverse_tree(ast->right, minishell, ast);
	}
	else if (node == PARENT_NODE)
	{
		ignore_signal_handler();
		clean_heredoc(ast->right, minishell);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

/* Function to remove heredoc node from main process for piped processes */
void	clean_heredoc(t_node *ast, t_minishell *minishell)
{
	int	i;
	int	heredoc_counter;

	i = 0;
	heredoc_counter = heredoc_count(ast->io_list);
	while (i < heredoc_counter)
	{
		remove_heredoc_node(&(minishell->heredoc_list));
		i++;
	}
}

/* Function to traverse and exec both left and right nodes of pipe */
t_node	*traverse_pipe(t_node *ast, t_minishell *minishell)
{
	int	pipefd[2];
	int	pid_l;
	int	pid_r;

	if (pipe_handler(pipefd, minishell) == 1)
		return (NULL);
	fork_handler(&pid_l, minishell);
	if (!pid_l)
	{
		redir_pipe(pipefd, minishell, LEFT_NODE, ast);
		free_data_and_exit(minishell);
	}
	fork_handler(&pid_r, minishell);
	clean_heredoc(ast->left, minishell);
	if (!pid_r)
	{
		redir_pipe(pipefd, minishell, RIGHT_NODE, ast);
		free_data_and_exit(minishell);
	}
	redir_pipe(pipefd, minishell, PARENT_NODE, ast);
	waitpid(pid_l, &minishell->exit_status, 0);
	waitpid(pid_r, &minishell->exit_status, 0);
	ft_exit_status(minishell);
	return (ast);
}
