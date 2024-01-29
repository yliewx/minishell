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

int	cd_error(char *arg, int error)
{
	printf("minishell: cd: ");
	if (error == CD_ARG)
		printf("too many arguments\n");
	else if (error == CD_NODIR)
		printf("%s: No such file or directory\n", arg);
	return (0);
}

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

int	unset_error(char *arg, int error)
{
	if (error == UNSET_PARAM)
		printf("minishell: unset: %s: invalid parameter name\n", arg);
	return (0);
}