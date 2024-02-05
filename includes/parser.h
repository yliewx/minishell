/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:33:33 by agan              #+#    #+#             */
/*   Updated: 2024/01/22 13:33:34 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_minishell t_minishell;
typedef struct s_heredoc t_heredoc;

typedef struct s_io_node
{
    t_token_type type;
    char *value;
    char *expanded_arg;
	struct s_io_node	*next;
}   t_io_node;

// Typedef for nodes of AST
typedef struct s_node
{
    t_token_type type;
    t_token_type next_binop;
    int is_heredoc;
    char *value;
    char *expanded;
    char **expanded_arg;
    t_io_node *io_list;
    struct s_node *left;
    struct s_node *right;
    t_minishell *minishell;
} t_node;

// Parser main
t_node *ft_parser(t_minishell *minishell);
t_node *ft_expression(t_minishell *minishell, int min_prec);

// Parser utils
int is_binop(t_token *token);
int is_redir(t_minishell *minishell);
int get_token_prec(t_token *token);
t_token *lookahead(t_minishell *minishell);
t_token *next_binop(t_minishell *minishell);

// Parser helper functions
void set_parse_err(int parse_err, t_minishell *minishell);
void ft_next_token(t_minishell *minishell);
t_node *ft_cmd(t_minishell *minishell);
t_node *ft_combine(t_minishell *minishell, t_token_type op, t_node *left, t_node *right);

// Node functions
t_node *ft_new_node(char *cmd, t_token_type type, t_minishell *minishell);
t_io_node *new_io_node(t_minishell *minishell, t_io_node **list);
void print_heredoc(t_heredoc *heredoc_list);
int heredoc_node(char *delimiter, t_heredoc **heredoc_list);

// Free ast functions
void ft_free_io_list(t_io_node **list);
void free_ast_nodes(t_node *node);
void free_ast(t_node **ast);

#endif
