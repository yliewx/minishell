/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:50:19 by agan              #+#    #+#             */
/*   Updated: 2024/02/06 17:50:20 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_node *parenthesis_handler(t_minishell *minishell, t_node **node)
{
    if (!lookahead(minishell))
        return (set_exit_error(minishell, SYNTAX_ERR, 1), 
            print_char_err(minishell, '('), NULL);
    ft_next_token(minishell);
    *node = ft_ast(minishell, 0);
    if (!*node)
        return (set_exit_error(minishell, MEM_ERR, 1), \
            print_str_err(minishell, NULL), NULL);
    if (!minishell->curr_token || minishell->curr_token->type != T_CLOSE)
        return (set_exit_error(minishell, SYNTAX_ERR, 1), \
            print_str_err(minishell, token_last(minishell->tokens)->value), NULL);
    ft_next_token(minishell);
    return (*node);
}

/* ft_cmd creates single node in ast
- Checks for syntax error for curr token
- Checks for open parenthesis -> creates node within parenthesis
- If no parenthesis
    - Checks for string -> creates string token
    - Handles redir and heredoc */
t_node *ft_cmd(t_minishell *minishell)
{
    t_node *node;
    
    node = NULL;
    if (is_binop(minishell->curr_token) || minishell->curr_token->type == T_CLOSE)
        return (set_exit_error(minishell, SYNTAX_ERR, 1), \
            print_str_err(minishell, minishell->curr_token->value), NULL);
    else if (minishell->curr_token->type == T_OPEN)
        parenthesis_handler(minishell, &node);
    else
    {
        if (minishell->curr_token->type == T_STRING)
        {
            node = ft_new_node(minishell->curr_token->value, minishell->curr_token->type, minishell);
            ft_next_token(minishell);
        }
        while (minishell->curr_token && is_redir(minishell))
        {
            if (minishell->curr_token->type == T_HEREDOC)
                node->is_heredoc = 1;
            new_io_node(minishell, &(node->io_list));
        }
    }
    return (node);
}