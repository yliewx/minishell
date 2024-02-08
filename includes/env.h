/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:34:59 by yliew             #+#    #+#             */
/*   Updated: 2024/02/02 12:35:02 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_minishell	t_minishell;

/*envp dup*/
void	envp_dup(t_minishell *minishell, char **envp);

/*sort envp*/
void	sort_envp(char **envp, int start, int end);

/*update envp*/
int		update_envp(t_minishell *minishell, char *var, \
	char *value, char *command);

/*search envp*/
int		search_envp_index(char **envp, char *var, int len);
char	*extract_var_name(char *arg);
char	*after_equal_sign(char *arg);
char	*value_in_env(char **envp, char *var, int len);

#endif
