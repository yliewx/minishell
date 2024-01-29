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

typedef struct s_minishell t_minishell;

typedef struct s_entry
{
	char	*name;
	struct s_entry	*next;
}	t_entry;

/*expander*/
void	get_expanded_arg(t_node *node);
void    check_wildcard(t_node *node, char **arg);

/*utils*/
char	*replace_with_value(char *arg, char *value, int start, int total_len);
char	*value_in_env(char **envp, char *var, int len);
bool	is_varname(int c);
bool    is_in_quote(char *c, char *arg, int quote);

/*readdir_utils*/
struct dirent	*ft_readdir(DIR *dir, struct dirent **entry);
t_entry	*create_entry_node(char *name);
void	append_entry(t_entry **list, t_entry *new);

#endif