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
	if (ft_strncmp(pattern, "..", 2) == 0)
		return (ft_strncmp(name, "..", 2) == 0);
	else if (pattern[0] == '.')
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
bool	match_pattern(t_pattern *pattern, char *curr_pattern, char *entry)
{
	int	i;
	int	j;

	if (pattern->start == curr_pattern && *pattern->start != '*'
		&& *pattern->start != *entry)
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
			return (match_pattern(pattern, curr_pattern + j, entry + i));
		i++;
	}
	return (false);
}

/* Function to extract the wildcard pattern from the argument */
void	extract_pattern(t_pattern *pattern, char *asterisk, char *arg)
{
	int		start;
	int		end;

	start = asterisk - arg;
	end = start;
	while (arg[start - 1] && arg[start - 1] != ' ')
		start--;
	while (arg[end + 1] && arg[end + 1] != ' ')
		end++;
	if (!arg[start - 1])
		end++;
	pattern->start = ft_substr(arg, start, end);
	pattern->start_index = start;
}
