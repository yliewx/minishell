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
# include "./lexer.h"
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

/*text colour*/

# define BROWN "\033[1;33m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define RESET "\033[0m"

// command table struct
/* nodes for linked list
- input/output fds
- command
- pointer to the next command
- pointer to t_data
*/
typedef struct s_command
{
	char	*token;
	char	**argv;
	/*char	*command;
	char	*flags;
	char	*arg;*/
	int	input_fd;
	int	output_fd;
	struct s_command	*next;
	struct s_data		*data;
}	t_command;

typedef struct s_history
{
	char				*input;
	struct s_history	*next;
	struct	s_data		*data;
}	t_history;

typedef struct s_data
{
	t_command	*command_list;
	t_history	*history_list;
	char		**envp;
	int		envp_size;
}	t_data;

enum e_errortype
{
	EXPORT_OPTION,
	EXPORT_IDENTIFIER,
};

/*builtins*/
int	check_builtin(t_data *data, t_command *current);
int	ft_echo(t_command *current);
int	ft_cd(t_data *data);
int	ft_pwd(t_data *data);
int	ft_export(t_data *data, t_command *current);
int	ft_unset(t_data *data, t_command *current);
int	ft_env(t_data *data);
int	ft_exit(t_data *data, t_command *current);

/*builtin_utils*/
void	update_envp(t_data *data, char *var, char *value, char *command);
int	search_envp_index(char **envp, char *var, int len);
char	*extract_var_name(char *arg);
int	export_error(char *arg, int error);
void	remove_quotes(char **arg);

/*expander*/
void	check_expand_variables(t_command *current, char *arg);

/*utils*/
void	array_dup(t_data *data, char **envp);
void	free_data(t_data *data);
char	**ft_split_argv(char *arg);
int	get_substr_len(char *arg, int delimiter, int i);

#endif