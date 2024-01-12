/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:32:12 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 17:32:23 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_data *data, t_command *current)
{
	char	*new_pwd;

	printf("command is %s\n", current->command);
	new_pwd = malloc(100 * sizeof(char));
	chdir("/home/yliew");
	getcwd(new_pwd, 100);
	printf("new_pwd: %s\n", new_pwd);
	update_env(data, "PWD", new_pwd);
	return (1);
}
