/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:05:30 by yliew             #+#    #+#             */
/*   Updated: 2023/10/16 17:59:38 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*COPIED FROM PIPEX - TO BE UPDATED*/

#include "pipex_bonus.h"

void	command_handler(char **argv, int index, char **envp)
{
	char	**child_argv;
	char	**path_array;
	char	*command_path;

	child_argv = NULL;
	path_array = NULL;
	command_path = NULL;
	get_child_argv(argv[index], &child_argv, count_tokens(argv[index]));
	if (*envp)
		path_array = get_env_path(envp);
	get_command_path(&command_path, child_argv[0], path_array);
	if (execve(command_path, child_argv, envp) == -1)
		perror_exit("Failed to execute command", EXIT_FAILURE);
}

int	count_tokens(char *arg)
{
	int	token_count;
	int	in_quote;
	int	i;

	token_count = 0;
	in_quote = 0;
	i = 0;
	while (arg[i])
	{
		if ((arg[i] == '\'' || arg[i] == '\"') && in_quote == 0)
			in_quote = arg[i];
		else if (arg[i] == in_quote)
			in_quote = 0;
		if (arg[i] != ' ' && (arg[i + 1] == ' ' || !(arg[i + 1]))
			&& in_quote == 0)
			token_count++;
		i++;
	}
	return (token_count);
}

void	get_child_argv(char *arg, char ***child_argv, int token_count)
{
	int	delimiter;
	int	start_len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	*child_argv = malloc((token_count + 1) * sizeof(char *));
	if (!*child_argv)
		perror_exit("Error allocating memory for child arguments", 127);
	while (j < token_count && arg[i])
	{
		delimiter = ' ';
		while (arg[i] && arg[i] == delimiter)
			i++;
		if (arg[i] == '\'' || arg[i] == '\"')
			delimiter = arg[i++];
		start_len = i;
		while (arg[i] && arg[i] != delimiter)
			i++;
		(*child_argv)[j++] = ft_substr(arg, start_len, i - start_len);
		i++;
	}
	(*child_argv)[token_count] = NULL;
}

/*retrieve possible file paths with envp and ft_split (shell command env)*/
char	**get_env_path(char **envp)
{
	char	**path;
	char	*start_pos;
	int		i;
	int		j;

	i = 0;
	while (envp[i] && (ft_strncmp(envp[i], "PATH", 4)) != 0)
		i++;
	start_pos = ft_strchr(envp[i], '=') + 1;
	path = ft_split(start_pos, ':');
	if (!path)
		perror_exit("Could not extract directory path", 127);
	j = 0;
	while (path[j])
	{
		path[j] = ft_strjoin(path[j], "/");
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
		perror_exit("Command not found", 127);
}
