/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:31:24 by agan              #+#    #+#             */
/*   Updated: 2024/01/29 17:31:25 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

void    exec_command(t_node *node, t_minishell *minishell);
char	**get_env_path(char **envp);
void	get_command_path(char **command_path, char *arg, char **path_array);
void    exec_simple_cmd(t_node *node, char **argv, t_minishell *minishell);
void    pipe_handler(t_node *node, int *pipefd);
int     open_handler(t_minishell *minishell, t_io_node *io_node, int *fd);
t_node *ft_exec(t_minishell *minishell);

#endif
