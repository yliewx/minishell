/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:44:19 by agan              #+#    #+#             */
/*   Updated: 2024/01/25 16:44:20 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if curr token is binop
int is_binop(t_token *token)
{
    if (token->type == T_AND || token->type == T_OR || token->type == T_PIPE)
        return (1);
    return (0);
}

// Function to check if token type is redirect
int is_redir(t_token *token)
{
    if (token->type == T_REDIR_L || \
    token->type == T_REDIR_R || \
    token->type == T_APPEND || \
    token->type == T_HEREDOC)
        return (1);
    return (0);
}

// Get curr token prec
int get_token_prec(t_token *token)
{
    if (token->type == T_AND || token->type == T_OR || token->type == T_PIPE)
        return (0);
    return (1);
}

// Lookahead function for next token
t_token *lookahead(t_minishell *minishell)
{
    t_token *token;

    token = NULL;
    if (minishell->curr_token)
        token = minishell->curr_token->next;
    return (token);
}

// Function to get the next binop token
t_token *next_binop(t_minishell *minishell)
{
    t_token *token;
    
    token = NULL;
    token = minishell->curr_token;
    while (token && !is_binop(token))
        token = token->next;
    return (token);
}

// Test: print io list
void print_node_list(t_node *node, t_io_node *list)
{
	while(list)
	{
        printf("node value %s\n", node->value);
		printf("%s\n", list->value);
		printf("%i\n", list->type);
		list = list->next;
	}
}


