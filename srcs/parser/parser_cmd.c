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
            print_str_err(minishell, "newline"), NULL);
    ft_next_token(minishell);
    return (*node);
}

t_node *parser_redir(t_minishell *minishell, t_node *node)
{
    while (minishell->curr_token && is_redir(minishell->curr_token))
    {
        if (minishell->curr_token->type == T_HEREDOC)
            node->is_heredoc = 1;
        if (!new_io_node(minishell, &(node->io_list)))
            return (NULL);
    }
    return (node);
}

t_token *get_curr_cmd(t_minishell *minishell)
{
    t_token *ret_token;

    ret_token = minishell->curr_token;
    while (ret_token && is_redir(ret_token))
    {
        ret_token = ret_token->next;
        if (ret_token->next && is_redir(ret_token->next))
            ret_token = ret_token->next;
    }
    if (ret_token->next && ret_token->next->type == T_STRING)
        return (ret_token->next);
    else
        return (NULL);
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
    t_token *curr_cmd;
    
    node = NULL;
    if (is_binop(minishell->curr_token) || minishell->curr_token->type == T_CLOSE)
        return (set_exit_error(minishell, SYNTAX_ERR, 1), \
            print_str_err(minishell, minishell->curr_token->value), NULL);
    else if (minishell->curr_token->type == T_OPEN)
        parenthesis_handler(minishell, &node);
    else
    {
        if (minishell->curr_token && is_redir(minishell->curr_token))
        {
            curr_cmd = get_curr_cmd(minishell);
            // Add error handling if curr token NULL
            if (!curr_cmd)
                return (NULL);
            node = ft_new_node(curr_cmd->value, curr_cmd->type, minishell);
            if (!node)
                return (NULL);
            if (!parser_redir(minishell, node))
                return (NULL);
            ft_next_token(minishell);
        }
        else if (minishell->curr_token && minishell->curr_token->type == T_STRING)
        {
            node = ft_new_node(minishell->curr_token->value, minishell->curr_token->type, minishell);
            if (!node)
                return (NULL);
            ft_next_token(minishell);
        }
        while (minishell->curr_token && is_redir(minishell->curr_token))
        {
            if (minishell->curr_token->type == T_HEREDOC)
                node->is_heredoc = 1;
            if (!new_io_node(minishell, &(node->io_list)))
                return (NULL);
        }
        // if (node->io_list)
        //     print_node_list(node, node->io_list);
    }
    return (node);
}


