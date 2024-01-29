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

// Dup2 handler -> open infile
    // handle if infile does not exists
    // Create if outfile does not exist
    // If append > O_APPEND
    // If heredoc > refer to here_doc pipe

// Pipe handler
    // Check t_token_type is pipe
    // Check io_list

// Exec_simple_cmd
    // Split and expand cmd
    // Fork
    // Exec
void exec_simple_cmd(t_node *node, char **argv, t_token_type parent_type, t_minishell *minishell)
{
    int pid;
    int pipe[2];
    char *command_path;

    pid = fork();
    if (pid == 0)
    {
        if (parent_type == PIPE)
            // Dup2 for pipe
        // Get path -> exec
        get_command_path(&command_path, argv[0], minishell->env_path);
        execve(command_path, argv, minishell->envp);
    }
    else
    {
        wait(&(minishell->exit_status))
    }
}
