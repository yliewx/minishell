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

// Create ast nodes
t_node *ft_new_node(char *cmd, t_token_type type, t_minishell *minishell)
{
    t_node *node;

    node = malloc(sizeof(t_node) * 1);
    if (!node)
        return (NULL);
    if (cmd)
        node->value = ft_strdup(cmd);
    else
        node->value = NULL;
    node->type = type;
    node->minishell = minishell;
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
        return (set_parse_err(1, minishell), NULL);
    node = malloc(sizeof(t_io_node));
    if (!node)
        return (NULL);
    node->type = minishell->curr_token->type;
    ft_next_token(minishell);
    node->value = ft_strdup(minishell->curr_token->value);
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
