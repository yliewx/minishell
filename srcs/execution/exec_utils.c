/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:40:05 by agan              #+#    #+#             */
/*   Updated: 2024/01/29 12:40:09 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		perror("Could not extract directory path\n");
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
		perror("Command not found\n");
}

// Dup2 handler -> open infile
    // handle if infile does not exists
    // Create if outfile does not exist
    // If append > O_APPEND
    // If heredoc > refer to here_doc pipe
int ft_dup(t_minishell *minishell, int oldfd, int newfd)
{
    int res;

    res = dup2(oldfd, newfd);
    if (res == -1)
        minishell->minishell_err = DUP2_ERR;
    return (res);
}

int open_handler(t_minishell *minishell, t_io_node *io_node, int *fd)
{
    if (io_node->type == T_APPEND)
        *fd = open(io_node->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (io_node->type == T_REDIR_L)
        *fd = open(io_node->value, O_RDONLY);
    else if (io_node->type == T_REDIR_R)
        *fd = open(io_node->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (*fd == -1)
        minishell->minishell_err = OPEN_ERR;
    return (*fd);
}

// Closing pipes

// Pipe handler
    // Check t_token_type is pipe
    // Check io_list
/*
void pipe_handler(t_node *node, int *pipefd)
{
    t_io_node *io_list;
    int fd;

    if (node->next_binop == T_PIPE)
    {
        pipe(pipefd);
        redir_handler(node->minishell, STDOUT_FILENO, pipefd[1]);
    }
    io_list = node->io_list;
    while (io_list)
    {
        if (open_handler(node->minishell, io_list, &fd) == -1)
            return ;
        if (io_list->type == T_REDIR_L)
            redir_handler(node->minishell, STDIN_FILENO, fd);
        else if (io_list->type == T_REDIR_R)
            redir_handler(node->minishell, STDOUT_FILENO, fd);
        else if (io_list->type == T_APPEND)
            redir_handler(node->minishell, STDOUT_FILENO, fd);
        else if (io_list->type == T_HEREDOC)
            redir_handler(node->minishell, STDIN_FILENO, node->minishell->here_doc[0]);
        io_list = io_list->next;
    }
}
*/
// Exec_simple_cmd
    // Split and expand cmd
    // Fork
    // Exec
void exec_simple_cmd(t_node *node, char **argv, t_minishell *minishell, int pid)
{
    char *command_path;

    (void)node;
    command_path = NULL;
    if (pid == 0)
    {
        //if (node->next_binop == T_PIPE)
            // Dup2 for pipe
        // Get path -> exec
        get_command_path(&command_path, argv[0], minishell->env_path);
        if (execve(command_path, argv, minishell->envp) == -1)
            perror("Execve() failed");
    }
    else
        wait(&(minishell->exit_status));
}
