/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:41:36 by yliew             #+#    #+#             */
/*   Updated: 2024/01/18 17:41:44 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_var_name(char *arg)
{
	char	*var_name;
	int		i;

	i = 0;
	if (!ft_strchr(arg, '='))
		return (arg);
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
		i++;
	var_name = ft_substr(arg, 0, i);
	return (var_name);
}

char	*after_equal_sign(char *arg)
{
	char	*str;

	str = ft_strchr(arg, '=');
	if (!str)
		return (NULL);
	return (str + 1);
}
