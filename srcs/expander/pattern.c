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
bool	match_pattern_suffix(char *curr_pattern, char *entry, int j)
{
	if (curr_pattern[j] != '*'
		&& (entry[ft_strlen(entry) - 1] != curr_pattern[j]))
		return (false);
	return (true);
}

/* Function to check if the file/directory name matches the pattern
- If the pattern does not begin with a *, check whether the name
starts with the same character as the pattern
- If the end of the pattern has been reached, check if the last character
in the pattern matches the last character in the name */
bool	match_pattern(t_node_arg *node_arg, char *curr_pattern, char *entry)
{
	int	i;
	int	j;

	if (node_arg->pattern == curr_pattern && *node_arg->pattern != '*'
		&& *node_arg->pattern != *entry)
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
			return (match_pattern(node_arg, curr_pattern + j, entry + i));
		i++;
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
	while (arg[start - 1] && !is_whitespace(arg[start - 1])
		&& !is_quote(arg[start - 1]))
		start--;
	while (arg[end + 1] && !is_whitespace(arg[end + 1])
		&& !is_quote(arg[end + 1]))
		end++;
	if (!arg[start - 1])
		end++;
	node_arg->pattern = ft_substr(arg, start, end - start + 1);
	node_arg->pattern_start = start;
}
