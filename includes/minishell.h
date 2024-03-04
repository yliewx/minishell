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
# include "./env.h"
# include "./error.h"

typedef struct s_heredoc
{
	char				*delimiter;
	int					pipefd[2];
	t_node				*node;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_minishell
{
	t_node		*ast;
	t_token		*tokens;
	t_token		*curr_token;
	t_heredoc	*heredoc_list;
	char		**envp;
	char		**env_path;
	char		*user;
	char		*prompt;
	int			envp_size;
	int			old_stdin;
	int			minishell_err;
	int			exit_status;
	int			heredoc_count;
	bool		heredoc_sigint;
}	t_minishell;

extern int	g_signum;

/*signals*/
void	readline_signal_handler(void);
void	ignore_signal_handler(void);
void	exec_signal_handler(int pid);
void	heredoc_signal_handler(int pid);

/*signal utils*/
void	set_g_signum(int signum);
void	sigint_write_nl(int signum);
void	sigint_readline(int signum);
void	sigint_exit(int signum);
void	sigquit_handler(int signum);

/*utils*/
int		arg_checker(int argc, char **argv);
int		ft_minishell(t_minishell *minishell);
void	ft_prompt(t_minishell *minishell);
char	*ft_readline(t_minishell *minishell);

/*init functions*/
void	init_minishell(t_minishell *minishell, bool start);
void	init_env(t_minishell *minishell, char **envp);

#endif
