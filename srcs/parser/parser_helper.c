/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:46:41 by agan              #+#    #+#             */
/*   Updated: 2024/01/25 16:46:42 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Move to next token
void ft_next_token(t_minishell *minishell)
{
    if (minishell->curr_token)
        minishell->curr_token = minishell->curr_token->next;
}

// Function to combine binop with left and right nodes
t_node *ft_combine(t_minishell *minishell, t_token_type op, t_node *left, t_node *right)
{
    t_node *binop;

    binop = ft_new_node(NULL, op, minishell);
    if (!binop)
        return (NULL);
    binop->left = left;
    binop->right = right;
    return (binop);
}
