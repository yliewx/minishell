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

/* Function to read from the current directory and set the value of entry
- Returns NULL if all entries have been read */
struct dirent	*ft_readdir(DIR *dir, struct dirent **entry)
{
	return (*entry = readdir(dir));
}

t_entry	*create_entry_node(char *value)
{
	t_entry	*new;

	new = malloc(sizeof(t_entry));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	append_entry(t_entry **list, t_entry *new)
{
	t_entry	*last_entry;

	if (!new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	last_entry = *list;
	while (last_entry->next)
		last_entry = last_entry->next;
	last_entry->next = new;
}

void	sort_entries(t_entry **list)
{
	t_entry	*current;
	t_entry	*temp;

	current = *list;
	while (current && current->next)
	{
		temp = current;
		while (temp && temp->next)
		{
			if (ft_strncmp(temp->value, temp->next->value,
					ft_strlen(temp->value)) > 0)
			{
				ft_swap(&temp->value, &temp->next->value);
				temp = *list;
			}
			else
				temp = temp->next;
		}
		current = current->next;
	}
}

void	free_match_list(t_entry **list)
{
	t_entry	*current;
	t_entry	*temp;

	current = *list;
	while (current && current->next)
	{
		temp = current->next;
		free(current->value);
		free(current);
		current = temp;
	}
	if (current)
	{
		free(current->value);
		free(current);
	}
}
