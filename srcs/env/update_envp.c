/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:07:29 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 18:07:35 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to resize the envp if a new variable is set or unset*/
char	**get_updated_envp(char **old_envp, int size, int remove_index, int *i)
{
	char	**new_envp;
	int		j;

	new_envp = malloc((size + 1) * sizeof(char *));
	if (!new_envp)
		return (NULL);
	j = 0;
	if (remove_index >= 0)
	{
		while (++(*i) < size)
		{
			if (j == remove_index)
				j++;
			new_envp[*i] = old_envp[j++];
		}
		free(old_envp[remove_index]);
	}
	else
	{
		while (++(*i) < size - 1)
			new_envp[*i] = old_envp[*i];
	}
	new_envp[*i] = NULL;
	return (new_envp);
}

int	resize_envp(t_minishell *minishell, int size, int remove_index)
{
	char	**old_envp;
	int		i;

	old_envp = minishell->envp;
	i = -1;
	minishell->envp_size = size;
	minishell->envp = get_updated_envp(old_envp, size, remove_index, &i);
	if (!minishell->envp)
		return (print_str_err(MEM_ERR, NULL, minishell), -1);
	free(old_envp);
	return (i);
}

/* Function to search for and update environment variables
- If the command is unset: removes the variable from envp if it exists
- If the command is export: adds the variable to envp if it does not exist
- Replaces the value of the variable if it exists in envp */
int	update_envp(t_minishell *minishell, char *var, char *value, \
	char *command)
{
	int	i;

	i = search_envp_index(minishell->envp, var);
	if (i >= 0)
	{
		if (ft_strncmp(command, "unset", 6) == 0 && !ft_strchr(var, '='))
			return (resize_envp(minishell, minishell->envp_size - 1, i));
		else if (value && ft_strchr(value, '='))
		{
			free(minishell->envp[i]);
			minishell->envp[i] = ft_strdup(value);
		}
	}
	else
	{
		if (ft_strncmp(command, "export", 7) == 0)
		{
			i = resize_envp(minishell, minishell->envp_size + 1, -1);
			if (i == -1)
				return (-1);
			minishell->envp[i] = ft_strdup(value);
			minishell->envp[i + 1] = NULL;
		}
	}
	return (0);
}
