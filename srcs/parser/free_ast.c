/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:43:29 by agan              #+#    #+#             */
/*   Updated: 2024/01/25 16:43:30 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_io_list(t_io_node **list)
{
    t_io_node *curr;
    t_io_node *next;

    curr = *list;
    if (!curr)
        return ;
    while (curr)
    {
        next = curr->next;
        free(curr->value);
        free(curr);
        curr = next;
    }
    *list = NULL;
}

void free_ast_nodes(t_node *node)
{
    if (!node)
        return ;
    if (node->left)
        free_ast_nodes(node->left);
    if (node->right)
        free_ast_nodes(node->right);
    if (node->value)
        free(node->value);
    if (node->io_list)
        ft_free_io_list(&node->io_list);
    free(node);
}

// Functions to free ast
void free_ast(t_node **ast)
{
    if (*ast)
    {
        free_ast_nodes(*ast);
        *ast = NULL;
    }
}