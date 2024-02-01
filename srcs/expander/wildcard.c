/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:26:38 by yliew             #+#    #+#             */
/*   Updated: 2024/01/26 14:26:41 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_match_in_dir(t_entry **match_list, t_pattern *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_entry			*new_match;

	dir = opendir(".");
	entry = NULL;
	while (ft_readdir(dir, &entry))
	{
		if (match_visibility(pattern->start, entry->d_name)
			&& match_pattern(pattern, pattern->start, entry->d_name))
		{
			new_match = create_entry_node(ft_strdup(entry->d_name));
			append_entry(match_list, new_match);
		}
	}
	closedir(dir);
}

void	join_entries(t_entry *match_list, char **expanded_value)
{
	char	*temp;

	*expanded_value = ft_calloc(1, sizeof(char));
	while (match_list)
	{
		temp = *expanded_value;
		*expanded_value = ft_strjoin(temp, match_list->name);
		free(temp);
		if (match_list->next)
		{
			temp = *expanded_value;
			*expanded_value = ft_strjoin(temp, " ");
			free(temp);
		}
		match_list = match_list->next;
	}
}

void	expand_wildcard(char **node_value, char **node_expanded, t_pattern *pattern)
{
	char	*new_str;
	int		new_len;

	new_len = ft_strlen(*node_value) - ft_strlen(pattern->start)
		+ ft_strlen(pattern->expanded_value);
	new_str = replace_with_value(*node_value, pattern->expanded_value,
		pattern->start_index, new_len);
	*node_expanded = new_str;
}

void    check_wildcard(char **node_value, char **node_expanded)
{
	t_entry	*match_list;
	t_pattern	pattern;
	char	*asterisk;

	asterisk = ft_strchr(*node_value, '*');
	if (!asterisk || !node_value || is_in_quote(asterisk, *node_value, '\'')
		|| is_in_quote(asterisk, *node_value, '\"'))
		return ;
	extract_pattern(&pattern, asterisk, *node_value);
	match_list = NULL;
	find_match_in_dir(&match_list, &pattern);
	if (match_list)
	{
		sort_entries(&match_list);
		join_entries(match_list, &pattern.expanded_value);
		expand_wildcard(node_value, node_expanded, &pattern);
	}
}
