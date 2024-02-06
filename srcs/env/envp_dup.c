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

void	envp_dup(t_minishell *minishell, char **envp)
{
	int	i;

	i = -1;
	minishell->envp_size = 0;
	if (!envp || !*envp)
		return ;
	while (envp[minishell->envp_size])
		minishell->envp_size++;
	if (search_envp_index(envp, "OLDPWD=", 7) == -1)
	{
		minishell->envp_size++;
		minishell->envp = malloc((minishell->envp_size + 1) * sizeof(char*));
		while (++i < minishell->envp_size - 1)
			minishell->envp[i] = ft_strdup(envp[i]);
		minishell->envp[i++] = init_oldpwd();
	}
	else
	{
		minishell->envp = malloc((minishell->envp_size + 1) * sizeof(char*));
		while (++i < minishell->envp_size)
			minishell->envp[i] = ft_strdup(envp[i]);
	}
	minishell->envp[i] = NULL;
	sort_envp(minishell->envp, 0, minishell->envp_size - 1);
}
