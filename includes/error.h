/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:02:21 by yliew             #+#    #+#             */
/*   Updated: 2024/02/05 14:02:39 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

typedef struct s_minishell	t_minishell;

enum e_minishell_err
{
	NO_ERR,
	SYNTAX_ERR,
	MEM_ERR,
	OPEN_ERR,
	PERM_ERR,
	DUP2_ERR,
	PIPE_ERR,
	FORK_ERR,
	EXEC_ERR,
	AMBIG_REDIR_ERR,
	CMD_NOT_FOUND_ERR,
	FILE_NOT_FOUND_ERR,
	CHILD_ERR,
};

enum e_builtin_err
{
	EXPORT_OPTION_ERR = 13,
	EXPORT_ID_ERR,
	PARAM_ERR,
	ARG_COUNT_ERR,
	NODIR_ERR,
	NOT_SET_ERR,
};

/* set exit status */
int		set_exit_success(t_minishell *minishell);
int		set_exit_error(t_minishell *minishell, int error, int status);
int		ft_exit_status(t_minishell *minishell);

/* print error messages */
// void 	print_char_err(t_minishell *minishell, char c);
// void 	print_str_err(t_minishell *minishell, char *str);
int		print_str_err(int error, char *str, t_minishell *minishell);
int		print_char_err(int error, char c, t_minishell *minishell);
void	print_err_helper(int error, char *str);

/* builtin errors */
int		cd_error(int error, char *arg, t_minishell *minishell);
int		exit_error(int error, char *arg, t_minishell *minishell);
int		export_error(int error, char *arg, t_minishell *minishell);
int		unset_error(int error, char *arg, t_minishell *minishell);

/* errors */
int		exec_error(int error, char *arg, t_minishell *minishell);
int		expander_error(int error, char *arg, t_minishell *minishell);
bool	is_ambiguous_redir(int io_type, t_entry **match_list);

/* free data */
void	free_data(t_minishell *minishell);
void	free_data_and_exit(t_minishell *minishell);
void	free_arrays(char ***array);

void	ft_reinit(t_minishell *minishell, char *command);

#endif
