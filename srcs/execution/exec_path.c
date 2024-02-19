/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:53:28 by agan              #+#    #+#             */
/*   Updated: 2024/02/01 15:53:28 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Retrieve possible file paths with envp and ft_split (shell command env) */
char	**get_env_path(char **envp, t_minishell *minishell)
{
	char	**path;
	char	*start_pos;
	char	*temp;
	int		i;
	int		j;

	i = search_envp_index(envp, "PATH", 4);
	if (i == -1)
		return (NULL);
	start_pos = ft_strchr(envp[i], '=') + 1;
	path = ft_split(start_pos, ':');
	if (!path)
		return (print_str_err(MEM_ERR, NULL, minishell), NULL);
	j = 0;
	while (path[j])
	{
		temp = path[j];
		path[j] = ft_strjoin(temp, "/");
		free(temp);
		j++;
	}
	return (path);
}

/* Check every directory in PATH until the command is found
- If no environment, check common paths */
void	get_command_path(char **command_path, char *arg, t_minishell *minishell)
{
	int		i;

	i = 0;
	if (!minishell->env_path)
	{
		*command_path = arg;
		if (access(*command_path, X_OK) == -1)
			exec_error(FILE_NOT_FOUND_ERR, arg, minishell);
		return ;
	}
	while (minishell->env_path[i])
	{
		if (ft_strncmp(arg, "/", 1) == 0 || ft_strnstr(arg, "./", 3))
			*command_path = arg;
		else
			*command_path = ft_strjoin(minishell->env_path[i], arg);
		if (access(*command_path, X_OK) == 0)
			return ;
		free(*command_path);
		i++;
	}
	if (!minishell->env_path[i])
		exec_error(CMD_NOT_FOUND_ERR, arg, minishell);
}
