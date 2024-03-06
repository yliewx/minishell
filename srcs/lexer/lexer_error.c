/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 16:19:30 by agan              #+#    #+#             */
/*   Updated: 2024/02/16 16:19:32 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to get curr type based on value 
- If redir, return 1
- If parenthesis, return 2 
- If binop, return 3 */
int	get_curr_type(char *line, int i)
{
	if (!ft_strncmp(line + i, ">>", 2))
		return (T_APPEND);
	if (!ft_strncmp(line + i, "<<", 2))
		return (T_HEREDOC);
	if (!ft_strncmp(line + i, ">", 1))
		return (T_REDIR_R);
	if (!ft_strncmp(line + i, "<", 1))
		return (T_REDIR_L);
	if (!ft_strncmp(line + i, "(", 1))
		return (T_OPEN);
	if (!ft_strncmp(line + i, ")", 1))
		return (T_CLOSE);
	if (!ft_strncmp(line + i, "&&", 2))
		return (T_AND);
	if (!ft_strncmp(line + i, "||", 2))
		return (T_OR);
	if (!ft_strncmp(line + i, "|", 1))
		return (T_PIPE);
	return (0);
}

/*
- If symbol not preceded with valid type, set err 
Invalid if:
- Preceded by symbol that is not a parenthesis
- Symbol is a redirect and preceded by parenthesis 
- Symbol is a open parenthesis preceded by string */
int	lexer_error(t_minishell *minishell, int curr_type)
{
	t_token_type	last_type;

	last_type = get_prev_type(minishell->tokens);
	if (((last_type != T_PIPE && last_type != T_STRING && \
		last_type != T_OPEN && last_type != T_CLOSE && \
		type_checker(curr_type) != L_BRACKET \
		&& last_type != T_NULL)) && \
		(type_checker(curr_type) != L_REDIR && \
		type_checker(last_type) != L_BINOP))
	{
		return (print_str_err(SYNTAX_ERR, \
			token_last(minishell->tokens)->value, minishell), -1);
	}
	if ((type_checker(curr_type) == L_REDIR && \
		type_checker(last_type) == L_BRACKET) || \
		(curr_type == T_OPEN && last_type == T_CLOSE))
	{
		return (print_str_err(SYNTAX_ERR, \
			token_last(minishell->tokens)->value, minishell), -1);
	}
	if ((curr_type == T_OPEN && last_type == T_STRING) || \
		(curr_type == T_CLOSE && last_type == T_OPEN))
		return (print_str_err(SYNTAX_ERR, \
			token_last(minishell->tokens)->value, minishell), -1);
	return (0);
}
