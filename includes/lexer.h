/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:21:10 by agan              #+#    #+#             */
/*   Updated: 2024/01/15 16:21:11 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

typedef enum e_token_type
{
	T_STRING,
	T_REDIR_L,
	T_REDIR_R,
	T_APPEND_L,
	T_APPEND_R,
	T_PIPE,
	T_O_BRACKET,
	T_C_BRACKET,
	T_AND,
	T_OR,
}	t_token_type;

typedef struct s_token
{
	char *value;
	t_token_type type;
	struct s_token *next;
	struct s_token *prev;
}	t_token;

t_token *create_node(char *content);
void token_add_back(t_token **token_list, t_token *new);
void print_token_list(t_token *token_list);

#endif
