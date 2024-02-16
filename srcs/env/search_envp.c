/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:41:36 by yliew             #+#    #+#             */
/*   Updated: 2024/01/18 17:41:44 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to search envp for a variable and return its index in the array */
int	search_envp_index(char **envp, char *var, int len)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/* Function to return a pointer to the string after the equal sign
- Return empty string if the equal sign does not exist
(variable is set but does not have a value) */
char	*after_equal_sign(char *arg)
{
	char	*str;

	str = ft_strchr(arg, '=');
	if (!str)
		return (ft_strdup(""));
	return (str + 1);
}

/* Function to return the value of a variable in envp */
char	*value_in_env(char **envp, char *var, int len)
{
	int	i;

	i = search_envp_index(envp, var, len);
	if (i >= 0)
	{
		if (envp[i][len - 1] != '=')
			return (after_equal_sign(envp[i]));
		return (envp[i] + len);
	}
	return (ft_strdup(""));
}

/* Function to extract the variable name from the arg
- Includes the equal sign if it is present */
char	*extract_var_name(char *arg)
{
	char	*var_name;
	int		i;

	i = 0;
	if (!ft_strchr(arg, '='))
		return (ft_strdup(arg));
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
		i++;
	var_name = ft_substr(arg, 0, i);
	return (var_name);
}
