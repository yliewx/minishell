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

typedef struct s_io_node
{
    t_token_type type;
    char *value;
    struct s_io_node	*prev;
	struct s_io_node	*next;
}   t_io_node;

// Typedef for nodes of AST
typedef struct s_node
{
    t_token_type type;
    char *value;
    char **expanded_value;
    t_io_node *io_list;
    struct s_node *left;
    struct s_node *right;
} t_node;

t_node *ft_parser(t_minishell *minishell);
t_node *ft_expression(t_minishell *minishell, int min_prec);
int get_token_prec(t_token *token);

#endif
