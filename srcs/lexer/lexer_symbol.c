/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:04:37 by agan              #+#    #+#             */
/*   Updated: 2024/02/06 11:04:37 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to create symbol token 
Create node with symbol type
Add to token_list 
Adds to i iterator based on token type */
t_token **create_symbol(t_token **token_list, char *val, t_token_type sym_type, int *i)
{
	t_token *token;
    char *symbol_value;

    symbol_value = ft_strdup(val);
    if (!symbol_value)
        return (NULL);
    token = create_node(symbol_value, sym_type);
	if (!token)
		return (NULL);
	token_add_back(token_list, token);
	if (sym_type == T_OR || sym_type == T_AND || sym_type == T_APPEND || sym_type == T_HEREDOC)
		*i += 2;
	else
		*i += 1;
	return (token_list);
}

/* Checks for symbol type using strncmp
If valid, create symbol token
Else write err and return NULL */
t_token **create_sym_token(t_token **token_list, char *line, int *i)
{
	if (!ft_strncmp(line + *i, "||", 2))
		return (create_symbol(token_list, "||", T_OR, i));
	else if (!ft_strncmp(line + *i, "|", 1))
		return (create_symbol(token_list, "|", T_PIPE, i));
	else if (!ft_strncmp(line + *i, ">>", 2))
		return (create_symbol(token_list, ">>", T_APPEND, i));
	else if (!ft_strncmp(line + *i, "<<", 2))
		return (create_symbol(token_list, "<<", T_HEREDOC, i));
	else if (!ft_strncmp(line + *i, "&&", 2))
		return (create_symbol(token_list, "&&", T_AND, i));
	else if (!ft_strncmp(line + *i, "<", 1))
		return (create_symbol(token_list, "<", T_REDIR_L, i));
	else if (!ft_strncmp(line + *i, ">", 1))
		return (create_symbol(token_list, ">", T_REDIR_R, i));
	else if (!ft_strncmp(line + *i, "(", 1))
		return (create_symbol(token_list, "(", T_OPEN, i));
	else if (!ft_strncmp(line + *i, ")", 1))
		return (create_symbol(token_list, ")", T_CLOSE, i));
	return (NULL);
}

t_token **sym_handler(t_minishell *minishell, t_token **token_list, char *line, int *i)
{
    if (!create_sym_token(token_list, line, i))
    {
        if (!minishell->minishell_err)
        {
            return (set_exit_error(minishell, SYNTAX_ERR, 1), \
			print_char_err(minishell, line[*i]), NULL);
        }
    }
    if (get_prev_type(*token_list) != T_STRING && get_prev_type(*token_list) != T_OPEN \
        && get_prev_type(*token_list) != T_CLOSE)
    {
        return (set_exit_error(minishell, SYNTAX_ERR, 1), \
			print_str_err(minishell, (token_last(*token_list))->value), NULL);
    }
    return (token_list);
}
