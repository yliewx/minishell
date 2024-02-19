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

/* Function to update PWD and OLDPWD value after changing directory
- Sets PWD and OLDPWD in envp if they do not exist */
void	update_pwd(t_minishell *minishell, char *oldpwd)
{
	char	*new_pwd;
	char	*new_pwd_temp;

	new_pwd_temp = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", new_pwd_temp);
	if (search_envp_index(minishell->envp, "PWD", 3) == -1)
		update_envp(minishell, "PWD", new_pwd, "export");
	else
		update_envp(minishell, "PWD", new_pwd, "cd");
	if (search_envp_index(minishell->envp, "OLDPWD", 6) == -1)
		update_envp(minishell, "OLDPWD", oldpwd, "export");
	else
		update_envp(minishell, "OLDPWD", oldpwd, "cd");
	free(new_pwd_temp);
	free(new_pwd);
}

/* Function to get the current working directory before changing directory */
char	*get_oldpwd(void)
{
	char	*oldpwd;
	char	*temp;

	temp = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", temp);
	free(temp);
	return (oldpwd);
}

/* Function to change to home directory
- Returns error if HOME is not set in envp */
int	cd_home(t_minishell *minishell, char *oldpwd)
{
	char	*home_path;

	home_path = value_in_env(minishell->envp, "HOME", 4);
	if (!home_path || !home_path[0])
	{
		free(home_path);
		return (cd_error(NOT_SET_ERR, NULL, minishell));
	}
	if (chdir(home_path) == -1)
		return (cd_error(NODIR_ERR, home_path, minishell));
	update_pwd(minishell, oldpwd);
	return (set_exit_success(minishell));
}

/* Function to change the current directory
- Returns to home directory if no argument is given
- Returns error if there is more than 1 argument */
int	ft_cd(t_minishell *minishell, t_node *node)
{
	char	*oldpwd;
	int		i;

	i = 0;
	while (node->expanded_arg[i])
		i++;
	if (i > 2)
		return (cd_error(ARG_COUNT_ERR, NULL, minishell));
	oldpwd = get_oldpwd();
	if (i == 1)
		return (cd_home(minishell, oldpwd), free(oldpwd), 0);
	if (chdir(node->expanded_arg[1]) == -1)
		return (free(oldpwd),
			cd_error(NODIR_ERR, node->expanded_arg[1], minishell));
	update_pwd(minishell, oldpwd);
	free(oldpwd);
	return (set_exit_success(minishell));
}
