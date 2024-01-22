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

// Typedef for nodes of AST
typedef struct s_node
{
    t_token_type type;
    char *value;
    char **expanded_value;
    struct s_node *left;
    struct s_node *right;
} t_node;

#endif
