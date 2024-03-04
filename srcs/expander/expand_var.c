/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:17:55 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 19:18:01 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to expand $? to the last exit status
- If g_signum is set, substitutes $? with 128 + signal number
- Else substitutes $? with the last exit status
- Returns the position after the exit status in the newly created string */
int	expand_exit_status(char **arg, int start, t_minishell *minishell)
{
	char	*new_str;
	char	*value;
	int		value_len;

	if (g_signum)
		value = ft_itoa(128 + g_signum);
	else
		value = ft_itoa(minishell->exit_status);
	value_len = ft_strlen(value);
	new_str = replace_var_with_value(*arg, value, start, 2);
	if (value)
		free(value);
	if (!new_str)
		return (print_str_err(MEM_ERR, NULL, minishell), -1);
	if (*arg)
		free(*arg);
	*arg = new_str;
	return (start + value_len);
}

/* Function to expand $(varname) to its value in the environment
- Returns the position after the value in the newly created string */
int	expand_var(char **arg, char *var_start, t_minishell *minishell)
{
	char	*var_name;
	char	*value;
	char	*new_str;
	int		var_len;
	int		pos_offset;

	var_name = get_var_name(var_start, &var_len);
	value = ft_strdup(value_in_env(minishell->envp, var_name + 1));
	if (!value)
		value = ft_strdup("");
	new_str = replace_var_with_value(*arg, value, var_start - *arg, var_len);
	pos_offset = var_start - *arg + ft_strlen(value);
	if (value)
		free(value);
	if (var_len)
		free(var_name);
	if (!new_str)
		return (print_str_err(MEM_ERR, NULL, minishell), -1);
	if (*arg)
		free(*arg);
	*arg = new_str;
	return (pos_offset);
}

/* Function to check for expandable $ and * symbols
- Skips consecutive $ symbols until the last $ is reached
- Checks what comes after the $ and expand if applicable
- If it has been expanded, continues from the returned position in the
new string such that the earlier segment of the string that has already
been checked will not be iterated over again */
int	ft_expand(char **arg, char **current, t_node_arg *node_arg)
{
	int	pos_offset;

	pos_offset = 0;
	while (*current && (*current)[1] == '$')
		(*current)++;
	if (*current && (*current)[0] == '$')
	{
		if ((*current)[1] == '?')
			pos_offset = expand_exit_status(arg, *current - *arg,
					node_arg->minishell);
		else if ((*current)[1] != ' ' && is_var_name((*current)[1]))
			pos_offset = expand_var(arg, *current, node_arg->minishell);
	}
	else if (*current && (*current)[0] == '*' && node_arg->in_quote == 0)
		pos_offset = check_wildcard(arg, *current, node_arg);
	if (pos_offset > 0)
		*current = *arg + pos_offset;
	else if (pos_offset == 0)
		(*current)++;
	return (pos_offset);
}

/* Function to iterate over the string until a quote is found
- Call ft_expand for every character in the string that is not within
single quotes
- If a single quote is encountered: skip to the end quote
- If a double quote is encountered: ft_expand $ but skip wildcards
- Return when the whole string has been checked or an error is found

echo '$HOME' -> DOES NOT expand
echo "$HOME" -> EXPANDS

echo 'hello world "$HOME"' -> DOES NOT expand
	bash:		hello world "$HOME"

echo 'hello world '$HOME'' -> EXPANDS
echo "hello world "$HOME"" -> EXPANDS
	bash:		hello world /home/user

echo "hello world '$HOME'" -> EXPANDS
	bash:		hello world '/home/user' */
int	ft_expand_quote_handler(char **arg, char *current, t_node_arg *node_arg)
{
	if (!current || !*current)
		return (0);
	while (*current && !is_quote(*current))
	{
		if (ft_expand(arg, &current, node_arg) == -1)
			return (-1);
	}
	if (current && *current)
	{
		if (*current == '\'')
			current = get_end_quote(current, '\'');
		else if (*current == '\"')
		{
			node_arg->in_quote = *current++;
			while (*current && *current != '\"')
			{
				if (ft_expand(arg, &current, node_arg) == -1)
					return (-1);
			}
		}
		if (current)
			current++;
	}
	node_arg->in_quote = 0;
	return (ft_expand_quote_handler(arg, current, node_arg));
}
