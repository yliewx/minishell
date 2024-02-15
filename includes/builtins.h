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

# include "minishell.h"

typedef struct s_minishell	t_minishell;

enum e_command_type
{
	CMD_SIMPLE,
	CMD_CD,
	CMD_ECHO,
	CMD_ENV,
	CMD_EXIT,
	CMD_EXPORT,
	CMD_PWD,
	CMD_UNSET,
};

/*builtins*/
int		check_builtin(t_node *node);
int		exec_builtin(t_node *node, int builtin_type, int pid, \
	t_token_type parent_type);
int		ft_echo(t_node *node);
int		ft_cd(t_minishell *minishell, t_node *node);
int		ft_pwd(t_minishell *minishell);
int		ft_export(t_minishell *minishell, t_node *node);
int		ft_unset(t_minishell *minishell, t_node *node);
int		ft_env(t_minishell *minishell);
int		ft_exit(t_minishell *minishell, t_node *node);

/*builtin utils*/
bool	is_fork_cmd(t_node *node, int type);
bool	is_export_without_arg(t_node *node, int type);

#endif