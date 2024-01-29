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

// Function to set error
// parse_err 1 = syntax err
// parse_err 2 = mem alloc err
void set_parse_err(int parse_err, t_minishell *minishell)
{
    minishell->minishell_err = parse_err;
}

// Move to next token
void ft_next_token(t_minishell *minishell)
{
    if (minishell->curr_token)
    {
        minishell->curr_token = minishell->curr_token->next;
    }
}

// get_cmd
    // Checks for syntax error (binop or close parenthesis = error)
    // Check for open parenthesis
        // Call ft_expr(0)
        // Checks if parenthesis is closed
    // Create node for cmd
        // Check redir
            // get_io_list
            // append to io_list variable
t_node *ft_cmd(t_minishell *minishell)
{
    t_node *node;
    
    node = NULL;
    if (is_binop(minishell->curr_token) || minishell->curr_token->type == T_CLOSE)
        return (set_parse_err(1, minishell), NULL);
    else if (minishell->curr_token->type == T_OPEN)
    {
        if (!lookahead(minishell))
            return (set_parse_err(MEM_ERR, minishell), NULL);
        ft_next_token(minishell);
        node = ft_expression(minishell, 0);
        if (!node)
            return (set_parse_err(MEM_ERR, minishell), NULL);
        if (!minishell->curr_token || minishell->curr_token->type != T_CLOSE)
            return (set_parse_err(SYNTAX_ERR, minishell), NULL);
        ft_next_token(minishell);
    }
    else
    {
        if (minishell->curr_token->type == T_STRING)
        {
            //printf("ft_cmd: current token is %s\n", minishell->curr_token->value);
            node = ft_new_node(minishell->curr_token->value, minishell->curr_token->type, minishell);
            ft_next_token(minishell);
            //printf("ft_cmd after: current token is %s\n", minishell->curr_token->value);
        }
        while (minishell->curr_token && is_redir(minishell))
            new_io_node(minishell, &(node->io_list));
    }
    return (node);
}

t_node *ft_combine(t_minishell *minishell, t_token_type op, t_node *left, t_node *right)
{
    t_node *binop;

    binop = ft_new_node(NULL, op, minishell);
    if (!binop)
        return (set_parse_err(SYNTAX_ERR, minishell), NULL);
    binop->left = left;
    binop->right = right;
    return (binop);
}
