/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:47:53 by agan              #+#    #+#             */
/*   Updated: 2024/01/25 16:47:54 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void node_init(t_node *node, char *cmd)
{
    node->expanded = NULL;
    node->expanded_arg = NULL;
    node->left = NULL;
    node->right = NULL;
    node->io_list = NULL;
    if (cmd)
        node->value = ft_strdup(cmd);
    else
        node->value = NULL;
}

// Create ast nodes
t_node *ft_new_node(char *cmd, t_token_type type, t_minishell *minishell)
{
    t_node *node;
    t_token *next_token;
    t_token *next_binop_node;

    next_token = lookahead(minishell);
    node = malloc(sizeof(t_node) * 1);
    if (!node)
        return (NULL);
    node_init(node, cmd);
    node->type = type;
    node->minishell = minishell;
    if (next_token)
    {
        next_binop_node = next_binop(minishell);
        if (next_binop_node)
            node->next_binop = next_binop_node->type;
        else
            node->next_binop = T_NULL;
    }
    else
        node->next_binop = T_NULL;
    return (node);
}

// io list functions
// Create io node
t_io_node *new_io_node(t_minishell *minishell, t_io_node **list)
{
    t_io_node *node;
    t_token *next_token;
    t_io_node *last;

    next_token = lookahead(minishell);
    if (!next_token || next_token->type != T_STRING)
        return (NULL);
    node = malloc(sizeof(t_io_node));
    if (!node)
        return (NULL);
    node->type = minishell->curr_token->type;
    node->next = NULL;
    ft_next_token(minishell);
    node->value = ft_strdup(minishell->curr_token->value);
    if (node->type == T_HEREDOC)
    {
        heredoc_node(minishell->curr_token->value, &minishell->heredoc_list);
        minishell->heredoc_count++;
    }
    node->expanded_arg = NULL;
    ft_next_token(minishell);
    if (!*list)
    {
        *list = node;
        return(node);
    }
    last = *list;
    while (last && last->next)
        last = last->next;
    last->next = node;
    return (node);
}

int heredoc_node(char *delimiter, t_heredoc **heredoc_list)
{
    t_heredoc *node;
    t_heredoc *last;

    node = malloc(sizeof(t_heredoc));
    if (!node)
        return (-1);
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
