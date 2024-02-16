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
# define LEXER_H

# include "minishell.h"

typedef struct s_minishell	t_minishell;

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

typedef enum e_lexer_type
{
	L_STRING,
	L_REDIR,
	L_BRACKET,
	L_BINOP
}	t_lexer_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Main
t_token			*ft_lexer(t_minishell *minishell, char *line);

// Lexer symbol functions
t_token			*sym_handler(t_minishell *minishell, char *line, int *i);
t_token			*create_symbol(t_minishell *minishell, char *val, \
	t_token_type sym_type, int *i);
t_token			*create_sym_token(t_minishell *minishell, char *line, int *i);

// Lexer error functions
int				lexer_error(t_minishell *minishell, int curr_type);
int				get_curr_type(char *line, int i);

// Lexer string functions
t_token			*create_str_token(t_minishell *minishell, char *line, \
	int i, int j);

// Lexer helper functions
int				quotes_checker(t_minishell *minishell, t_token *token_list);

// Lexer tokens functions
int				command_iterator(char *line, int *i);
int				redir_iterator(char *line, int *i);
int				find_next_token(t_minishell *minishell, char *line, int *i);

// Lexer list functions
t_token			*create_node(char *content, t_token_type type);
t_token			*token_last(t_token *lst);
void			token_add_back(t_token **token_list, t_token *new);

// Lexer utils
void			skip_spaces(char *line, int *i);
int				is_symbol(char c);
t_token_type	get_prev_type(t_token *token_list);
t_lexer_type	type_checker(t_token_type type);
int				quote_found(char c);
/* void			print_token_list(t_token *token_list); */

// Free tokens
void			ft_free_token_list(t_token **lst);

#endif
