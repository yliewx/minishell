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
- If the previous process was interrupted by a signal,
substitutes $? with 128 + signal number
- Else substitutes $? with the last exit status
- Returns the position after the exit status in the newly created string */
int	expand_exit_status(t_minishell *minishell, char **arg, int start)
{
	char	*new_str;
	char	*value;
	int		value_len;

	if (g_signal.signum)
		value = ft_itoa(128 + g_signal.signum);
	else
		value = ft_itoa(minishell->exit_status);
	value_len = ft_strlen(value);
	new_str = replace_var_with_value(*arg, value, start, 2);
	free(value);
	if (!new_str)
		return (print_str_err(MEM_ERR, NULL, minishell), -1);
	free(*arg);
	*arg = new_str;
	return (start + value_len);
}

/* Function to expand $(varname) to its value in the environment
- Returns the position after the value in the newly created string */
int	expand_var(t_minishell *minishell, char **arg, char *var_start)
{
	char	*var_name;
	char	*value;
	char	*new_str;
	int		var_len;
	int		next_start_pos;

	var_name = get_var_name(var_start, &var_len);
	value = value_in_env(minishell->envp, var_name + 1, var_len - 1);
	if (!value)
		value = ft_strdup("");
	new_str = replace_var_with_value(*arg, value, var_start - *arg, var_len);
	next_start_pos = var_start - *arg + ft_strlen(value);
	if (ft_strlen(value) == 0)
		free(value);
	free(var_name);
	if (!new_str)
		return (print_str_err(MEM_ERR, NULL, minishell), -1);
	free(*arg);
	*arg = new_str;
	return (next_start_pos);
}

/* Function to check if the variable can be expanded
- If it has been expanded,
returns the position after the value in the newly created string */
int	check_if_expanded(t_minishell *minishell, char **arg, char *current)
{
	int		next_start_pos;

	next_start_pos = 0;
	if (current[1] == '?')
		next_start_pos = expand_exit_status(minishell, arg, current - *arg);
	else if (current[1] != ' ' && is_var_name(current[1]))
		next_start_pos = expand_var(minishell, arg, current);
	return (next_start_pos);
}

/* Function to find the first $ present in the string
- Skips the contents of single quotes if any
- Skips consecutive $ symbols until the last $ is reached
- Checks what comes after the $ and expand if applicable
- If it has been expanded, continues from the returned position in the
new string such that the earlier segment of the string that has already
been checked will not be iterated over again
- Returns if there are no more variables to be expanded */
int	check_expandable_var(t_minishell *minishell, char **arg, char *current)
{
	int	next_start_pos;

	if (!current || !current[0])
		return (0);
	current = ft_strchr(current, '$');
	if (!current)
		return (0);
	if (ft_strchr(current, '\'') && skip_quotes(current, *arg))
		current = get_end_quote(current + 1, '\'');
	while (current && current[1] && current[1] == '$')
		current++;
	if (current && current[0] == '$')
	{
		next_start_pos = check_if_expanded(minishell, arg, current);
		if (next_start_pos == -1)
			return (-1);
		else if (next_start_pos > 0)
			current = *arg + next_start_pos;
		else
			current++;
	}
	return (check_expandable_var(minishell, arg, current));
}
