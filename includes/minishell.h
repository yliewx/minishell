/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:26:50 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 15:32:03 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>

// command table struct
/* nodes for linked list
- input/output fds
- command
- pointer to the next command
- pointer to t_data
*/
typedef struct s_command
{
	char	**command; //char* or char**?
	int	input_fd;
	int	output_fd;
	struct s_command	*next;
	struct s_data		*data;
}	t_command;

typedef struct s_data
{
	t_command	*command_list;
	char	**new_envp;
}	t_data;

/*builtins*/
int	check_builtin(t_data *data, t_command *current);
int	ft_echo(t_data *data, t_command *current);
int	ft_cd(t_data *data, t_command *current);
int	ft_pwd(t_data *data, t_command *current);
int	ft_export(t_data *data, t_command *current);
int	ft_unset(t_data *data, t_command *current);
int	ft_env(t_data *data, t_command *current);
int	ft_exit(t_data *data, t_command *current);
void	update_env(t_data *data, char *var, char *value);

/*utils*/
void	array_dup(t_data *data, char **envp);

#endif
