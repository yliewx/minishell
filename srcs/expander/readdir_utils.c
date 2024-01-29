/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:45:37 by yliew             #+#    #+#             */
/*   Updated: 2024/01/26 16:45:43 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct dirent	*ft_readdir(DIR *dir, struct dirent **entry)
{
	return (*entry = readdir(dir));
}

t_entry	*create_entry_node(char *name)
{
	t_entry	*new;

	new = malloc(sizeof(t_entry));
	if (!new)
		return (NULL);
	new->name = name;
	new->next = NULL;
	return (new);
}

t_entry	*get_last_entry(t_entry **list)
{
	t_entry	*current;

	current = *list;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	append_entry(t_entry **list, t_entry *new)
{
	if (!new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	get_last_entry(list)->next = new;
}