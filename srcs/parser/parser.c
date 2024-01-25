/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:59:02 by agan              #+#    #+#             */
/*   Updated: 2024/01/22 13:59:03 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Error handling

// Print tree

// parse_expression(min_prec)
// Lookahead = peek next token
    // Get left term with compute_node()
        // Op = lookahead
        // While lookahead is binop && precedence >= min_prec
        // Right = ft_expression(precedence of op + 1 if lookahead precedence is greater)
t_node *ft_expression(t_minishell *minishell, int min_prec)
{
    t_node *left;
    t_node *right;
    t_token_type op;
    
    left = ft_cmd(minishell);
    if (!left)
        return (NULL);
    while (minishell->curr_token && is_binop(minishell->curr_token) && \
        get_token_prec(minishell->curr_token) >= min_prec)
    {
        op = minishell->curr_token->type;
        ft_next_token(minishell);
        right = ft_expression(minishell, get_token_prec(minishell->curr_token) + 1);
        if (!right)
            return (NULL);
        left = ft_combine(minishell, op, left, right);
        printf("left being returned is %s\n", left->value);
        printf("left node is %s\n", left->left->value);
        printf("right node is %s\n", left->right->value);
        if (!left)
            return (NULL);
    }
    // printf("single node returned %s\n", left->value);
    // printf("single node's t_token_type %d\n", left->io_list->type);
    // printf("single node's io_list val %s\n", left->io_list->value);
    return (left);
}

// Parser to run prescedence climbing function
t_node *ft_parser(t_minishell *minishell)
{
    if (minishell->curr_token)
        minishell->ast = ft_expression(minishell, 0);
    return (minishell->ast);
}