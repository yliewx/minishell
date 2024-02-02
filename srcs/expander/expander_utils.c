/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:26:27 by yliew             #+#    #+#             */
/*   Updated: 2024/01/26 14:26:31 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (arg[++start] == '?')
		start++;
	else
	{
		while (arg[start] && is_varname(arg[start]))
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

/*echo "hello world '$HOME'"
	hello world '/home/[path]'
echo 'hello world "$HOME"'
	hello world "$HOME"
*/
bool    is_in_quote(char *c, char *arg, int quote)
{
	char	*start_quote;
	char	*end_quote;

	start_quote = ft_strchr(arg, quote);
	end_quote = ft_strrchr(arg, quote);
	if (!start_quote || !end_quote)
		return (false);
	if (quote == '\'')
    {
		if (is_in_quote(start_quote, arg, '\"')
			&& (c > start_quote && c < end_quote))
            return (false);
    }
    return (c > start_quote && c < end_quote);
}