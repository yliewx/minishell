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

struct dirent	*ft_readdir(DIR *dir, struct dirent **entry)
{
	return (*entry = readdir(dir));
}

char	**find_match_in_dir(void)
{
	DIR	*dir;
	struct dirent	*entry;

	dir = opendir(".");
	entry = NULL;
	while (ft_readdir(dir, &entry))
	{
		printf("%s\n", entry->d_name);
	}
	closedir(dir);
	return (NULL);
}

void    check_wildcard(t_command *current, char **arg)
{
    char	*asterisk;

	asterisk = ft_strchr(*arg, '*');
	if (!asterisk || !current)
		return ;
    printf("asterisk: %s\n", asterisk);
	find_match_in_dir();
}