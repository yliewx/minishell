/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:26:27 by yliew             #+#    #+#             */
/*   Updated: 2024/01/26 14:26:31 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_var_name(int c)
{
	return (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		|| c == '_');
}

char	*get_var_name(char *var_start, int *var_len)
{
	*var_len = 1;
	while (var_start[*var_len] && is_var_name(var_start[*var_len]))
		(*var_len)++;
	return (ft_substr(var_start, 0, *var_len));
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
	if (arg[++start] == '?')
		start++;
	else
	{
		while (arg[start] && is_var_name(arg[start]))
			start++;
	}
	j = 0;
	while (value[j])
		new_str[i++] = value[j++];
	while (i < total_len)
		new_str[i++] = arg[start++];
	new_str[i] = '\0';
	return (new_str);
}
