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
		|| c == '_' || (c >= '0' && c <= '9'));
}

/* Function to extract the variable name including the preceding $ */
char	*get_var_name(char *var_start, int *var_len)
{
	*var_len = 1;
	while (var_start[*var_len] && is_var_name(var_start[*var_len]))
		(*var_len)++;
	return (ft_substr(var_start, 0, *var_len));
}

/* Function to replace the $ variable name with its value
- Copies the original string up to the "start" position
(the index of the $ to be replaced)
- Shifts the position in the original string to the end of the variable name
- Copies the variable's value into the new string
- Continues copying from the position in the original string */
char	*copy_and_replace(char *arg, char *value, int start, int total_len)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = ft_calloc(total_len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < start)
		new_str[i] = arg[i];
	if (arg[++start] == '?')
		start++;
	else
	{
		while (arg[start] && (!is_whitespace(arg[start])
				&& !is_quote(arg[start])))
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

char	*replace_var_with_value(char *arg, char *value, int start, int var_len)
{
	int	new_str_len;

	new_str_len = ft_strlen(arg) - var_len + ft_strlen(value);
	return (copy_and_replace(arg, value, start, new_str_len));
}
