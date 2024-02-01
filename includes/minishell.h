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
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <fcntl.h>
# include "./lexer.h"
# include "./parser.h"
# include "./builtins.h"
# include "./expander.h"
# include "./exec.h"

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

typedef struct s_heredoc
{
	char	*delimiter;
	int		pipefd[2];
	struct s_heredoc *next;
} 	t_heredoc;

typedef struct s_minishell
{
	t_node *ast;
	t_token *tokens;
	t_token *curr_token;
	t_heredoc *heredoc_list;
	char	**envp;
	char	**env_path;
	int		envp_size;
	int		heredoc_count;
	int 	minishell_err;
	int 	exit_status;
}	t_minishell;

typedef struct s_history
{
	char				*input;
	struct s_history	*next;
	struct	s_data		*data;
}	t_history;

enum e_minishell_err
{
	SYNTAX_ERR,
	MEM_ERR,
	OPEN_ERR,
	DUP2_ERR,
	PIPE_ERR,
	FORK_ERR,
	EXEC_ERR
};

/*utils*/
void	array_dup(t_minishell *minishell, char **envp);
void	sort_envp(char **envp, int start, int end);
void	ft_swap(char **a, char **b);
void	free_data(t_minishell *minishell);
char	**ft_split_argv(char *arg);
bool	is_quote(int c);
void	init_signals(t_minishell *minishell);

#endif
