/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:44:31 by yliew             #+#    #+#             */
/*   Updated: 2024/01/17 18:44:37 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_error(char *arg, int error)
{
	printf("minishell: export: ");
	if (error == EXPORT_IDENTIFIER)
		printf("`%s': not a valid identifier\n", arg);
	else if (error == EXPORT_OPTION)
	{
		printf("-%c: invalid option\n" , arg[1]);
		printf("export: usage: export [name[=value] ...]\n");
	}
	return (0);
}
