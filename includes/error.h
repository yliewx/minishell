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

typedef struct s_minishell t_minishell;

enum e_minishell_err
{
	NO_ERR,
	SYNTAX_ERR,
	MEM_ERR,
	OPEN_ERR,
	DUP2_ERR,
	PIPE_ERR,
	FORK_ERR,
	EXEC_ERR,
	AMBIG_REDIR_ERR,
};

enum e_builtin_err
{
	EXPORT_OPTION = 10,
	EXPORT_IDENTIFIER,
	UNSET_PARAM,
	CD_ARG,
	CD_NODIR,
};

/*free data*/
void	free_data(t_minishell *minishell);
void	free_data_and_exit(t_minishell *minishell);
void	free_arrays(char ***array);

#endif
