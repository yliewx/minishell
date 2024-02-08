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
t_token	*create_symbol(t_minishell *minishell, char *val, \
t_token_type sym_type, int *i)
{
	t_token	*token;
	char	*symbol_value;

	symbol_value = ft_strdup(val);
	if (!symbol_value)
		return (print_str_err(MEM_ERR, NULL, minishell), NULL);
	token = create_node(symbol_value, sym_type);
	if (!token)
		return (print_str_err(MEM_ERR, NULL, minishell), NULL);
	token_add_back(&minishell->tokens, token);
	if (sym_type == T_OR || sym_type == T_AND || \
		sym_type == T_APPEND || sym_type == T_HEREDOC)
		*i += 2;
	else
		*i += 1;
	return (minishell->tokens);
}

/* Checks for symbol type using strncmp
If valid, create symbol token
Else write err and return NULL */
t_token	*create_sym_token(t_minishell *minishell, char *line, int *i)
{
	if (!ft_strncmp(line + *i, "||", 2))
		return (create_symbol(minishell, "||", T_OR, i));
	else if (!ft_strncmp(line + *i, "|", 1))
		return (create_symbol(minishell, "|", T_PIPE, i));
	else if (!ft_strncmp(line + *i, ">>", 2))
		return (create_symbol(minishell, ">>", T_APPEND, i));
	else if (!ft_strncmp(line + *i, "<<", 2))
		return (create_symbol(minishell, "<<", T_HEREDOC, i));
	else if (!ft_strncmp(line + *i, "&&", 2))
		return (create_symbol(minishell, "&&", T_AND, i));
	else if (!ft_strncmp(line + *i, "<", 1))
		return (create_symbol(minishell, "<", T_REDIR_L, i));
	else if (!ft_strncmp(line + *i, ">", 1))
		return (create_symbol(minishell, ">", T_REDIR_R, i));
	else if (!ft_strncmp(line + *i, "(", 1))
		return (create_symbol(minishell, "(", T_OPEN, i));
	else if (!ft_strncmp(line + *i, ")", 1))
		return (create_symbol(minishell, ")", T_CLOSE, i));
	return (NULL);
}

t_token	*sym_handler(t_minishell *minishell, char *line, int *i)
{
	if (!create_sym_token(minishell, line, i))
	{
		if (!minishell->minishell_err)
			return (print_char_err(SYNTAX_ERR, line[*i], minishell), NULL);
		return (NULL);
	}
	if (get_prev_type(minishell->tokens) != T_STRING && \
		get_prev_type(minishell->tokens) != T_OPEN \
		&& get_prev_type(minishell->tokens) != T_CLOSE)
	{
		return (print_str_err(SYNTAX_ERR, \
			token_last(minishell->tokens)->value, minishell), NULL);
	}
	return (minishell->tokens);
}
