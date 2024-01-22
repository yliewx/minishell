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

// Set error

// Create node
    // Assign arg
    // Return node

// get_cmd
    // Checks for syntax error (binop or close parenthesis = error)
    // Check for open parenthesis
        // Call ft_expr(0)
        // Checks if parenthesis is closed
    // Create node for cmd
        // Check redir
            // get_io_list
            // append to io_list variable

// get io_list

// parse_expression(min_prec)
// Lookahead = peek next token
    // Get left term with compute_node()
        // Op = lookahead
        // While lookahead is binop && precedence >= min_prec
        // Right = ft_expression(precedence of op + 1 if lookahead precedence is greater)

// Get curr token prec

// Checks if curr token is binary op

// peek next token func

// Parser to run prescedence climbing function
// void parser(t_minishell minishell)
// {

// }