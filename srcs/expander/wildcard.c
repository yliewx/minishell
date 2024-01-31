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

bool	match_visibility(char *pattern, char *name)
{
	printf("pattern: %s, name: %s\n", pattern, name);
	if (ft_strncmp(pattern, "..", 2) == 0)
		return (ft_strncmp(name, "..", 2) == 0);
	else if (pattern[0] == '.')
		return (name[0] == '.');
	else if (name[0] == '.')
		return (false);
	return (true);
}

/*
echo *ft*c | wc -w //c must be the last letter of the name
49
echo *ft*c* | wc -w
63
*/
bool	match_pattern_suffix(char *curr_pattern, char *entry, int j)
{
	if (curr_pattern[j] != '*'
		&& (entry[ft_strlen(entry) - 1] != curr_pattern[j]))
		return (false);
	return (true);
}

bool	match_pattern(char *pattern_start, char *curr_pattern, char *entry)
{
	int	i;
	int	j;

	if (pattern_start == curr_pattern && *pattern_start != '*'
		&& *pattern_start != *entry)
		return (false);
	while (curr_pattern && *curr_pattern == '*')
		curr_pattern++;
	i = 0;
	while (entry[i])
	{
		j = 0;
		while (curr_pattern[j] && curr_pattern[j] != '*')
		{
			if (entry[i + j] != curr_pattern[j])
				break ;
			j++;
		}
		if (!curr_pattern[j])
			return (match_pattern_suffix(curr_pattern, entry, j - 1));
		else if (curr_pattern[j] == '*')
			return (match_pattern(pattern_start, curr_pattern + j, entry + i));
		i++;
	}
	return (false);
}

void	find_match_in_dir(t_entry **match_list, char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_entry			*new_match;

	dir = opendir(".");
	entry = NULL;
	while (ft_readdir(dir, &entry))
	{
		printf("%s\n", entry->d_name);
		if (match_visibility(pattern, entry->d_name)
			&& match_pattern(pattern, pattern, entry->d_name))
		{
			printf(GREEN"%s is a match\n\n"RESET, entry->d_name);
			new_match = create_entry_node(entry->d_name);
			append_entry(match_list, new_match);
		}
		else
			printf(RED"%s does not match\n\n"RESET, entry->d_name);
	}
	closedir(dir);
}

void	extract_pattern(char **pattern, char *arg, char *asterisk)
{
	int		start;
	int		end;

	start = asterisk - arg;
	end = start;
	while (arg[start - 1] && arg[start - 1] != ' ')
		start--;
	while (arg[end + 1] && arg[end + 1] != ' ')
		end++;
	*pattern = ft_substr(arg, start, end);
}

void	expand_wildcard(t_entry *match_list, t_node *node, char *pattern)
{
	char	*temp;
	char	*expanded_value;

	expanded_value = ft_calloc(1, sizeof(char));
	while (match_list)
	{
		temp = expanded_value;
		expanded_value = ft_strjoin(temp, match_list->name);
		free(temp);
		if (match_list->next)
		{
			temp = expanded_value;
			expanded_value = ft_strjoin(temp, " ");
			free(temp);
		}
		match_list = match_list->next;
	}
	if (node || pattern)
		printf("expanded value: %s\n", expanded_value);
}

void    check_wildcard(t_node *node, char **arg)
{
	t_entry	*match_list;
	char	*asterisk;
	char	*pattern;

	asterisk = ft_strchr(*arg, '*');
	if (!asterisk || is_in_quote(asterisk, *arg, '\'')
		|| is_in_quote(asterisk, *arg, '\"') || !node)
		return ;
	extract_pattern(&pattern, *arg, asterisk);
	printf("pattern: %s (len: %li)\n", pattern, ft_strlen(pattern));
	match_list = NULL;
	find_match_in_dir(&match_list, pattern);
	//test print
	sort_entries(&match_list);
	int i = 0;
	t_entry	*temp = match_list;
	printf("\n\nAFTER SORT:\n\n");
	while (temp)
	{
		printf("entry[%i]: %s\n", i++, temp->name);
		temp = temp->next;
	}
	expand_wildcard(match_list, node, pattern);
}
