/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:06:38 by yliew             #+#    #+#             */
/*   Updated: 2024/01/31 18:06:40 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to check if the visibility status of the file/directory
matches the visibility status specified in the pattern */
bool	match_visibility(char *pattern, char *name)
{
	if (pattern[0] == '.')
		return (name[0] == '.');
	else if (name[0] == '.')
		return (false);
	return (true);
}

/* Function to check if the last character in the file/directory name
matches the pattern
- If the pattern does not end with *, check that the name ends with
the same character */
bool	match_pattern_suffix(char *c_pattern, char *entry, int j)
{
	if (c_pattern[j] != '*'
		&& (entry[ft_strlen(entry) - 1] != c_pattern[j]))
		return (false);
	return (true);
}

/* Function to check if the first character in the entry name
matches the pattern
- If the pattern does not begin with a *, check whether the name
starts with the same character as the pattern */
bool	match_pattern_prefix(t_node_arg *node_arg, char *c_pattern, char *entry)
{
	if (node_arg->pattern == c_pattern && *node_arg->pattern != '*'
		&& *node_arg->pattern != *entry)
		return (false);
	return (true);
}

/* Function to check if the file/directory name matches the pattern
- When reaching the end of the pattern and entry points to null after last char,
return true
- If the end of the pattern has been reached, check if the last character
in the pattern matches the last character in the name */
bool	match_pattern(t_node_arg *node_arg, char *c_pattern, char *entry)
{
	int	i;
	int	j;

	if (!match_pattern_prefix(node_arg, c_pattern, entry))
		return (false);
	else if (c_pattern && *c_pattern == '*' && !(*entry) && !*(c_pattern + 1))
		return (true);
	while (c_pattern && *c_pattern == '*')
		c_pattern++;
	i = -1;
	while (entry[++i])
	{
		j = 0;
		while (c_pattern[j] && c_pattern[j] != '*')
		{
			if (entry[i + j] != c_pattern[j])
				break ;
			j++;
		}
		if (!c_pattern[j])
			return (match_pattern_suffix(c_pattern, entry, j - 1));
		else if (c_pattern[j] == '*')
			return (match_pattern(node_arg, c_pattern + j, entry + i + 1));
	}
	return (false);
}

/* Function to extract the wildcard pattern from the argument */
void	extract_pattern(char *arg, char *asterisk, t_node_arg *node_arg)
{
	int		start;
	int		end;

	start = asterisk - arg;
	end = start;
	if (start != 0)
	{
		while (start >= 0 && arg[start] && !is_whitespace(arg[start])
			&& !is_quote(arg[start]))
			start--;
		start++;
	}
	while (arg[end] && !is_whitespace(arg[end])
		&& !is_quote(arg[end]))
		end++;
	node_arg->pattern = ft_substr(arg, start, end - start);
	node_arg->pattern_start = start;
}
