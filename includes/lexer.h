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
	T_APPEND,
	T_HEREDOC,
	T_PIPE,
	T_OPEN,
	T_CLOSE,
	T_AND,
	T_OR,
	T_NULL
}	t_token_type;

typedef struct s_token
{
	char *value;
	t_token_type type;
	struct s_token *next;
	struct s_token *prev;
}	t_token;

// Main
t_token *ft_lexer(char *line);

// Lexer helper functions
t_token **create_str_token(t_token **token_list, char *line, int i, int j);
t_token **create_symbol(t_token **token_list, t_token_type sym_type, int *i);
t_token **create_sym_token(t_token **token_list, char *line, int *i);
int find_next_token(t_token **token_list, char *line, int *i);
int quotes_checker(t_token *token_list);

// Lexer list functions
t_token *create_node(char *content, t_token_type type);
t_token	*token_last(t_token *lst);
void token_add_back(t_token **token_list, t_token *new);

// Lexer utils
void print_token_list(t_token *token_list);
void skip_spaces(char *line, int *i);
int is_symbol(char c);

// Free tokens
void ft_free_token_list(t_token **lst);

#endif
