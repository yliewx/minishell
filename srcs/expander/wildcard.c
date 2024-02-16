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

/* Function to iterate through all entries in the current directory
- Check whether the entry matches the pattern and visibility
- If it does, append it to the linked list */
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

/* Function to combine all the matched entries into 1 string*/
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

/* Function to substitute the wildcard pattern with the matched value */
int	expand_wildcard(char **expanded_str, t_pattern *pattern, \
	t_minishell *minishell)
{
	char	*new_str;

	new_str = replace_var_with_value(*expanded_str, pattern->expanded_value,
			pattern->start_index, ft_strlen(pattern->start));
	if (!new_str)
		return (print_str_err(MEM_ERR, NULL, minishell), -1);
	free(*expanded_str);
	*expanded_str = new_str;
	return (0);
}

/* Function to check whether * wildcards are present in the arg
- Extract the wildcard pattern if it exists
- Create a linked list of all entries in directory that match the pattern
- If more than 1 entry matches and the current arg is a redirect value,
return amiguous redirect error
- Sort entries in alphabetical order and combine them into 1 string
- Expands the pattern in the original string */
int	check_wildcard(char **expanded_str, int io_type, t_minishell *minishell)
{
	t_entry		*match_list;
	t_pattern	pattern;
	char		*asterisk;

	asterisk = ft_strchr(*expanded_str, '*');
	if (!asterisk || is_in_quote(asterisk, '\'') || is_in_quote(asterisk, '\"'))
		return (0);
	extract_pattern(&pattern, asterisk, *expanded_str);
	match_list = NULL;
	find_match_in_dir(&match_list, &pattern);
	if (match_list)
	{
		if (is_ambiguous_redir(io_type, &match_list))
		{
			expander_error(AMBIG_REDIR_ERR, pattern.start, minishell);
			return (free(pattern.start), -1);
		}
		sort_entries(&match_list);
		join_entries(match_list, &pattern.expanded_value);
		if (expand_wildcard(expanded_str, &pattern, minishell) == -1)
			return (free_match_list(&match_list), free(pattern.start), -1);
		free_match_list(&match_list);
	}
	return (free(pattern.start), 0);
}
