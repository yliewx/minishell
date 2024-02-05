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

/*retrieve possible file paths with envp and ft_split (shell command env)*/
char	**get_env_path(char **envp)
{
	char	**path;
	char	*start_pos;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], "PATH", 4)) != 0)
		i++;
	start_pos = ft_strchr(envp[i], '=') + 1;
	path = ft_split(start_pos, ':');
	if (!path)
		perror("Could not extract directory path\n");
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

/*check every directory in PATH until the command is found
- if no environment, just check common paths*/
void	get_command_path(char **command_path, char *arg, char **path_array)
{
	char	*default_arr[4];
	int		i;

	i = 0;
	if (!path_array)
	{
		default_arr[0] = "/bin/";
		default_arr[1] = "/usr/bin/";
		default_arr[2] = "/usr/local/bin/";
		default_arr[3] = NULL;
		path_array = default_arr;
	}
	while (path_array[i])
	{
		if (ft_strncmp(arg, "/", 1) == 0 || ft_strnstr(arg, "./", 3))
			*command_path = arg;
		else
			*command_path = ft_strjoin(path_array[i], arg);
		if (access(*command_path, X_OK) == 0)
			return ;
		free(*command_path);
		i++;
	}
	if (!path_array[i])
		perror("Command not found\n");
}
