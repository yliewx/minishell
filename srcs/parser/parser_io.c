/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:10:10 by agan              #+#    #+#             */
/*   Updated: 2024/02/07 11:10:10 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	io_node_init(t_minishell *minishell, t_io_node *node)
{
	node->type = minishell->curr_token->type;
	node->next = NULL;
	node->expanded_arg = NULL;
	ft_next_token(minishell);
	node->value = ft_strdup(minishell->curr_token->value);
}

void	io_add_back(t_io_node *node, t_io_node **list)
{
	t_io_node	*last;

	if (!*list)
	{
		*list = node;
		return ;
	}
	last = *list;
	while (last && last->next)
		last = last->next;
	last->next = node;
}

/* Creates io nodes as a linked list */
t_io_node	*new_io_node(t_minishell *minishell, t_io_node **list)
{
	t_io_node	*node;
	t_token		*next_token;

	next_token = lookahead(minishell);
	if (!next_token || next_token->type != T_STRING)
		return (print_str_err(SYNTAX_ERR, "newline", minishell), NULL);
	node = malloc(sizeof(t_io_node));
	if (!node)
		return (print_str_err(MEM_ERR, NULL, minishell), NULL);
	io_node_init(minishell, node);
	if (node->type == T_HEREDOC)
	{
		if (heredoc_node(minishell, minishell->curr_token->value, \
			&minishell->heredoc_list) == -1)
			return (NULL);
		minishell->heredoc_count++;
	}
	ft_next_token(minishell);
	io_add_back(node, list);
	return (node);
}

/* Function to create heredoc nodes linked list */
int	heredoc_node(t_minishell *minishell, char *delimiter, \
t_heredoc **heredoc_list)
{
	t_heredoc	*node;
	t_heredoc	*last;

	node = malloc(sizeof(t_heredoc));
	if (!node)
		return (print_str_err(MEM_ERR, NULL, minishell), -1);
	node->delimiter = ft_strdup(delimiter);
	node->next = NULL;
	if (!*heredoc_list)
	{
		*heredoc_list = node;
		return (0);
	}
	last = *heredoc_list;
	while (last && last->next)
		last = last->next;
	last->next = node;
	return (0);
}
