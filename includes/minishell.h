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

# include "libft.h"

// command table struct
/* nodes for linked list
- input/output fds
- command
- pointer to the next command
- pointer to t_data
*/
typedef struct s_command
{
	char	*command; //char* or char**?
	int	input_fd;
	int	output_fd;
	struct s_command	*next;
	struct s_data		*data;
}	t_command;

typedef struct s_data
{
	char	**new_envp;
}	t_data;

#endif
