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

void	update_pwd(t_data *data)
{
	char	*new_pwd;
	char	*new_pwd_temp;
	char	*old_pwd;
	char	*old_pwd_temp;

	new_pwd_temp = getcwd(NULL, 0);
	new_pwd = ft_strjoin("PWD=", new_pwd_temp);
	old_pwd_temp = ft_strdup(data->envp[search_envp_index(data->envp,
		"PWD=", 4)]);
	old_pwd = ft_strjoin("OLDPWD=", old_pwd_temp + 4);
	update_envp(data, "PWD=", new_pwd, "cd");
	update_envp(data, "OLDPWD=", old_pwd, "cd");
	free(new_pwd_temp);
	free(old_pwd_temp);
	free(new_pwd);
	free(old_pwd);
}

int	ft_cd(t_data *data, t_command *current)
{
	int		i;

	i = 0;
	while (current->argv[i])
		i++;
	if (i > 2)
		return (cd_error(NULL, CD_ARG), 1);
	if (chdir(current->argv[1]) == -1)
		return (cd_error(current->argv[1], CD_NODIR), 1);
	update_pwd(data);
	return (1);
}