/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:23:41 by yliew             #+#    #+#             */
/*   Updated: 2024/01/24 15:24:04 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"

typedef struct s_data t_data;
typedef struct s_command t_command;

enum e_errortype
{
	EXPORT_OPTION,
	EXPORT_IDENTIFIER,
	UNSET_PARAM,
	CD_ARG,
	CD_NODIR,
};

/*builtins*/
int	check_builtin(t_data *data, t_command *current);
int	ft_echo(t_command *current);
int	ft_cd(t_data *data, t_command *current);
int	ft_pwd(t_data *data);
int	ft_export(t_data *data, t_command *current);
int	ft_unset(t_data *data, t_command *current);
int	ft_env(t_data *data);
int	ft_exit(t_data *data);

/*builtin_utils*/
void	update_envp(t_data *data, char *var, char *value, char *command);
int	search_envp_index(char **envp, char *var, int len);
char	*extract_var_name(char *arg);
char	*after_equal_sign(char *arg);
void	remove_quotes(char **arg);

/*builtin errors*/
int	cd_error(char *arg, int error);
int	export_error(char *arg, int error);
int	unset_error(char *arg, int error);

#endif