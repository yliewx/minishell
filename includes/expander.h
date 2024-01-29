/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:41:00 by yliew             #+#    #+#             */
/*   Updated: 2024/01/26 14:41:06 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

#include "minishell.h"

typedef struct s_data t_data;
typedef struct s_command t_command;

/*expander*/
void	expand_argv(t_command *current);
void    check_wildcard(t_command *current, char **arg);

/*utils*/
char	*replace_with_value(char *arg, char *value, int start, int total_len);
char	*value_in_env(char **envp, char *var, int len);
bool	is_varname(int c);
bool    is_in_quote(char *c, char *arg, int quote);

#endif