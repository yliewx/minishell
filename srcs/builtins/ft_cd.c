/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:32:12 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 17:32:23 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_minishell *minishell)
{
	char	*new_pwd;
	char	*new_pwd_temp;
	char	*old_pwd;
	char	*old_pwd_temp;

	new_pwd_temp = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", new_pwd_temp);
	old_pwd_temp = ft_strdup(\
		minishell->envp[search_envp_index(minishell->envp, "PWD=", 4)]);
	old_pwd = ft_strjoin("OLDPWD=", old_pwd_temp + 4);
	update_envp(minishell, "PWD=", new_pwd, "cd");
	update_envp(minishell, "OLDPWD=", old_pwd, "cd");
	free(new_pwd_temp);
	free(old_pwd_temp);
	free(new_pwd);
	free(old_pwd);
}

int	cd_home(t_minishell *minishell)
{
	char	*home_path;

	home_path = value_in_env(minishell->envp, "HOME=", 5);
	if (chdir(home_path) == -1)
		return (cd_error(NODIR_ERR, home_path, minishell));
	update_pwd(minishell);
	return (set_exit_success(minishell));
}

int	ft_cd(t_minishell *minishell, t_node *node)
{
	int		i;

	i = 0;
	while (node->expanded_arg[i])
		i++;
	if (i == 1)
		return (cd_home(minishell));
	if (i > 2)
		return (cd_error(ARG_COUNT_ERR, NULL, minishell));
	if (chdir(node->expanded_arg[1]) == -1)
		return (cd_error(NODIR_ERR, node->expanded_arg[1], minishell));
	update_pwd(minishell);
	return (set_exit_success(minishell));
}
