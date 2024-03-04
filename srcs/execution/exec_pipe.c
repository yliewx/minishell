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
	}
	else if (node == RIGHT_NODE)
	{
		close(pipefd[1]);
		ft_dup(minishell, pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	else if (node == PARENT_NODE)
	{
		ignore_signal_handler();
		close(pipefd[0]);
		close(pipefd[1]);
		clean_heredoc(ast, minishell);
	}
}

void	clean_heredoc(t_node *ast, t_minishell *minishell)
{
	int	i;
	int	heredoc_counter;

	i = 0;
	heredoc_counter = heredoc_count(ast->left->io_list) + \
		heredoc_count(ast->right->io_list);
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
		traverse_tree(ast->left, minishell, ast);
		free_data_and_exit(minishell);
	}
	fork_handler(&pid_r, minishell);
	if (!pid_r)
	{
		redir_pipe(pipefd, minishell, RIGHT_NODE, ast);
		traverse_tree(ast->right, minishell, ast);
		free_data_and_exit(minishell);
	}
	redir_pipe(pipefd, minishell, PARENT_NODE, ast);
	waitpid(pid_l, &minishell->exit_status, 0);
	waitpid(pid_r, &minishell->exit_status, 0);
	ft_exit_status(minishell);
	return (ast);
}
