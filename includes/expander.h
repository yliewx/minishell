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

# include "minishell.h"

typedef struct s_minishell	t_minishell;

typedef struct s_node_arg
{
	char		*pattern;
	char		*expanded_value;
	int			pattern_start;
	int			io_type;
	int			in_quote;
	t_minishell	*minishell;
}	t_node_arg;

typedef struct s_entry
{
	char			*value;
	struct s_entry	*next;
}	t_entry;

/*expander*/
int				get_expanded_arg(t_node *node, t_minishell *minishell);
int				ft_expand_quote_handler(char **arg, char *current, \
	t_node_arg *node_arg);
int				ft_expand(char **arg, char **current, t_node_arg *node_arg);
int				check_wildcard(char **arg, char *asterisk, \
	t_node_arg *node_arg);

/*utils*/
char			*replace_var_with_value(char *arg, char *value, \
	int start, int var_len);
char			*get_var_name(char *var_start, int *var_len);
bool			is_var_name(int c);

/*ft_split_argv*/
char			**ft_split_argv(char *arg);
char			**ft_split_whitespace(char const *s);
bool			is_quote(int c);
bool			is_whitespace(char c);

/*quotes handler utils*/
bool			is_in_quote(char *c, int quote);
bool			skip_quotes(char *c, char *full_arg);
char			*get_end_quote(char *c, int quote);
char			*remove_quotes(char *arg);
int				remove_expanded_arg_quotes(char **arg);
int				remove_expanded_argv_quotes(char **argv);

/*pattern*/
void			extract_pattern(char *arg, char *asterisk, \
	t_node_arg *pattern);
bool			match_pattern(t_node_arg *pattern, char *curr_pattern, \
	char *entry);
bool			match_visibility(char *pattern, char *value);

/*readdir_utils*/
struct dirent	*ft_readdir(DIR *dir, struct dirent **entry);
t_entry			*create_entry_node(char *value);
void			append_entry(t_entry **list, t_entry *new);
void			free_match_list(t_entry **list);
void			sort_entries(t_entry **list);

#endif