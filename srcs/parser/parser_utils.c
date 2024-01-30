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
