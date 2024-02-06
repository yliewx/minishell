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

typedef struct s_pattern
{
	char	*start;
	char	*expanded_value;
	int		start_index;
}	t_pattern;

typedef struct s_entry
{
	char	*name;
	struct s_entry	*next;
}	t_entry;

/*expander*/
void	get_expanded_arg(t_node *node);
void    check_wildcard(char **node_value, char **node_expanded);

/*utils*/
char	*replace_with_value(char *arg, char *value, int start, int total_len);
char	*get_var_name(char *var_start, int *var_len);
bool	is_var_name(int c);
bool    is_in_quote(char *c, int quote);
bool	skip_quotes(char *c, char *full_arg);
char	*get_end_quote(char *c, int quote);

/*pattern*/
void	extract_pattern(t_pattern *pattern, char *asterisk, char *arg);
bool	match_pattern(t_pattern *pattern, char *curr_pattern, char *entry);
bool	match_visibility(char *pattern, char *name);

/*readdir_utils*/
struct dirent	*ft_readdir(DIR *dir, struct dirent **entry);
t_entry	*create_entry_node(char *name);
void	append_entry(t_entry **list, t_entry *new);
void	free_match_list(t_entry **list);
void	sort_entries(t_entry **list);

#endif