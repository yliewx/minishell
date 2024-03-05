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
void	find_match_in_dir(t_entry **match_list, t_node_arg *node_arg)
{
	DIR				*dir;
	struct dirent	*entry;
	t_entry			*new_match;

	dir = opendir(".");
	entry = NULL;
	while (ft_readdir(dir, &entry))
	{
		if (match_visibility(node_arg->pattern, entry->d_name)
			&& match_pattern(node_arg, node_arg->pattern, entry->d_name))
		{
			new_match = create_entry_node(entry->d_name);
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
		*expanded_value = ft_strjoin(temp, match_list->value);
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
int	expand_wildcard(char **arg, t_node_arg *node_arg)
{
	char	*new_str;

	new_str = replace_var_with_value(*arg, node_arg->expanded_value,
			node_arg->pattern_start, ft_strlen(node_arg->pattern));
	if (!new_str)
		return (print_str_err(MEM_ERR, NULL, node_arg->minishell), -1);
	free(*arg);
	*arg = new_str;
	return (0);
}

/* Function to check whether * wildcards are present in the arg
- Extract the wildcard pattern if it exists
- Create a linked list of all entries in directory that match the pattern
- If more than 1 entry matches and the current arg is a redirect value,
return amiguous redirect error
- Sort entries in alphabetical order and combine them into 1 string
- Expands the pattern in the original string */
int	check_wildcard(char **arg, char *asterisk, t_node_arg *node_arg)
{
	t_entry		*match_list;
	int			pos;

	extract_pattern(*arg, asterisk, node_arg);
	match_list = NULL;
	pos = 0;
	find_match_in_dir(&match_list, node_arg);
	if (match_list)
	{
		if (is_ambiguous_redir(node_arg->io_type, &match_list))
		{
			expander_error(AMBIG_REDIR_ERR,
				node_arg->pattern, node_arg->minishell);
			return (free(node_arg->pattern), -1);
		}
		sort_entries(&match_list);
		join_entries(match_list, &node_arg->expanded_value);
		pos = node_arg->pattern_start + ft_strlen(node_arg->expanded_value);
		if (expand_wildcard(arg, node_arg) == -1)
			return (free_match_list(&match_list), free(node_arg->pattern),
				free(node_arg->expanded_value), -1);
		free(node_arg->expanded_value);
		free_match_list(&match_list);
	}
	return (free(node_arg->pattern), pos);
}
