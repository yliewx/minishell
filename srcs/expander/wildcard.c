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
	{
		return (ft_strncmp(name, "..", 2) == 0);
	}
	else if (ft_strncmp(pattern, ".", 1) == 0)
	{
		return (ft_strncmp(name, ".", 1) == 0);
	}
	else if (name[0] == '.')
		return (false);
	return (true);
}
/*
bool match_pattern(char *pattern, char *asterisk, char *name)
{

}
*/
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
		if (match_visibility(pattern, entry->d_name))
		{
			new_match = create_entry_node(entry->d_name);
			append_entry(match_list, new_match);
		}
	}
	closedir(dir);
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
	pattern = *arg;
	printf("pattern: %s\n", pattern);
	match_list = NULL;
	find_match_in_dir(&match_list, pattern);

	//test print
	t_entry	*temp = match_list;
	int	i = 0;
	while (temp)
	{
		printf("entry[%i]: %s\n", i++, temp->name);
		temp = temp->next;
	}
}
