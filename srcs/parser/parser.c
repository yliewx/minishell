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

// Function to set error
// parse_err 1 = syntax err
// parse_err 2 = mem alloc err
void set_parse_err(int parse_err, t_minishell *minishell)
{
    minishell->parse_err = parse_err;
}

// Move to next token
void ft_next_token(t_minishell *minishell)
{
    if (minishell->curr_token)
        minishell->curr_token = minishell->curr_token->next;
}

// Checks if curr token is binary op
int is_binop(t_token *token)
{
    if (token->type == T_AND || token->type == T_OR || token->type == T_PIPE)
        return (1);
    return (0);
}

// Function to check if token type is redirect
int is_redir(t_minishell *minishell)
{
    if (minishell->curr_token->type == T_REDIR_L || \
    minishell->curr_token->type == T_REDIR_R || \
    minishell->curr_token->type == T_APPEND || \
    minishell->curr_token->type == T_HEREDOC)
        return (1);
    return (0);
}

// Create ast nodes
t_node *ft_new_node(char *cmd, t_token_type type)
{
    t_node *node;

    node = malloc(sizeof(t_node));
    if (!node)
        return (NULL);
    node->value = cmd;
    node->type = type;
    return (node);
}

// Lookahead function for next token
t_token *lookahead(t_minishell *minishell)
{
    t_token *token;

    token = minishell->curr_token->next;
    return (token);
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
    
    if (is_binop(minishell->curr_token) || minishell->curr_token->type == T_CLOSE)
        return (set_parse_err(1, minishell), NULL);
    else if (minishell->curr_token->type == T_OPEN)
    {
        ft_next_token(minishell);
        node = ft_expression(minishell, 0);
        if (!node)
            return (set_parse_err(2, minishell), NULL);
        if (!minishell->curr_token || minishell->curr_token->type != T_CLOSE)
            return (set_parse_err(1, minishell), NULL);
        ft_next_token(minishell);
    }
    else 
    {
        if (minishell->curr_token->type == T_STRING)
        {
            node = ft_new_node(minishell->curr_token->value, minishell->curr_token->type);
            ft_next_token(minishell);
            if (!node)
                return (NULL);
        }
        while (minishell->curr_token && is_redir(minishell))
            new_io_node(minishell, &(node->io_list));
    }
    return (node);
}

t_node *ft_combine(t_minishell *minishell, t_token_type op, t_node *left, t_node *right)
{
    t_node *binop;

    binop = ft_new_node(NULL, op);
    if (!binop)
        set_parse_err(1, minishell);
    binop->left = left;
    binop->right = right;
    return (binop);
}

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
    while (is_binop(minishell->curr_token) && get_token_prec(minishell->curr_token) >= min_prec)
    {
        op = minishell->curr_token->type;
        ft_next_token(minishell);
        right = ft_expression(minishell, get_token_prec(minishell->curr_token) + 1);
        if (!right)
            return (NULL);
        left = ft_combine(minishell, op, left, right);
        if (!left)
            return (NULL);
    }
    return (left);
}

// Get curr token prec
int get_token_prec(t_token *token)
{
    if (token->type == T_AND || token->type == T_OR || token->type == T_PIPE)
        return (0);
    return (1);
}

// Parser to run prescedence climbing function
t_node *ft_parser(t_minishell *minishell)
{
    if (minishell->curr_token)
        minishell->ast = ft_expression(minishell, 0);
    return (minishell->ast);
}