/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:17:55 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 19:18:01 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*value_in_env(char **envp, char *var, int len)
{
	int	i;

	i = search_envp_index(envp, var, len);
	if (i >= 0)
		return (envp[i] + len + 1);
	return (NULL);
}

bool	is_varname(int c)
{
	return (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		|| c == '_');
}

char	*replace_with_value(char *arg, char *value, int start, int total_len)
{
	char	*new_str;
	int	i;
	int	j;

	new_str = malloc((total_len + 1) * sizeof(char));
	i = -1;
	while (++i < start)
		new_str[i] = arg[i];
	start++;
	while (arg[start] && is_varname(arg[start]))
		start++;
	j = 0;
	while (value[j])
		new_str[i++] = value[j++];
	while (i < total_len)
		new_str[i++] = arg[start++];
	new_str[i] = '\0';
	return (new_str);
}

void	check_expand_variables(t_command *current, char *arg)
{
	char	*var_start;
	char	*var_name;
	char	*value;
	int	var_len;

	var_start = ft_strchr(arg, '$');
	if (!var_start)
		return ;
	var_len = 1;
	while (var_start[var_len] && is_varname(var_start[var_len]))
		var_len++;
	var_name = ft_substr(var_start, 0, var_len);
	value = value_in_env(current->data->envp, var_name + 1, var_len - 1);
	if (!value)
	{
		free(var_name);
		return ;
	}
	arg = replace_with_value(arg, value, var_start - arg,
		ft_strlen(current->argv[1]) - var_len + ft_strlen(value));
	free(current->argv[1]);
	free(var_name);
	current->argv[1] = arg;
	check_expand_variables(current, current->argv[1]);
}
