/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:51:03 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 16:51:04 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_oldpwd(void)
{
	char	*oldpwd;
	char	*temp;

	temp = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", temp);
	free(temp);
	return (oldpwd);
}

char	**get_new_envp(char **envp, int envp_size, int max_to_copy)
{
	char	**new_envp;
	int		i;

	new_envp = malloc((envp_size + 1) * sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = -1;
	while (++i < max_to_copy)
		new_envp[i] = ft_strdup(envp[i]);
	if (max_to_copy != envp_size)
		new_envp[i++] = init_oldpwd();
	new_envp[i] = NULL;
	return (new_envp);
}

void	envp_dup(t_minishell *minishell, char **envp)
{
	minishell->envp_size = 0;
	if (!envp || !*envp)
		return ;
	while (envp[minishell->envp_size])
		minishell->envp_size++;
	if (search_envp_index(envp, "OLDPWD=", 7) == -1)
	{
		minishell->envp_size++;
		minishell->envp = get_new_envp(envp, minishell->envp_size,
				minishell->envp_size - 1);
	}
	else
		minishell->envp = get_new_envp(envp, minishell->envp_size,
				minishell->envp_size);
	if (minishell->envp == NULL)
	{
		print_str_err(MEM_ERR, NULL, minishell);
		return ;
	}
	sort_envp(minishell->envp, 0, minishell->envp_size - 1);
}
