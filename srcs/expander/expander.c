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

void	expand_exit_status(t_minishell *minishell, char **arg, int start)
{
	char	*new_str;
	char	*value;

	value = ft_itoa(minishell->exit_status);
	new_str = replace_with_value(*arg, value, start,
		ft_strlen(*arg) - 2 + ft_strlen(value));
	free(value);
	free(*arg);
	*arg = new_str;
}

void	expand_var_value(t_minishell *minishell, char **arg, char *var_start)
{
	char	*new_str;
	char	*var_name;
	char	*value;
	int		var_len;

	var_len = 1;
	while (var_start[var_len] && is_varname(var_start[var_len]))
		var_len++;
	var_name = ft_substr(var_start, 0, var_len);
	value = value_in_env(minishell->envp, var_name + 1, var_len - 1);
	new_str = replace_with_value(*arg, value, var_start - *arg,
		ft_strlen(*arg) - var_len + ft_strlen(value));
	if (ft_strlen(value) == 0)
		free(value);
	free(var_name);
	free(*arg);
	*arg = new_str;
}

void	check_expandable_vars(t_minishell *minishell, char **arg)
{
	char	*var_start;

	var_start = ft_strchr(*arg, '$');
	if (!var_start || !var_start[1]
		|| (var_start && is_in_quote(var_start, *arg, '\'')))
		return ;
	if (var_start[1] == '?')
		expand_exit_status(minishell, arg, var_start - *arg);
	else if (var_start[1] != ' ')
			expand_var_value(minishell, arg, var_start);
	check_expandable_vars(minishell, arg);
}

void	get_expanded_arg(t_node *node)
{
	if (node && node->value)
	{
		check_expandable_vars(node->minishell, &node->value);
		check_wildcard(&node->value, &node->expanded);
		if (node->expanded)
			node->expanded_arg = ft_split_argv(node->expanded);
		else
			node->expanded_arg = ft_split_argv(node->value);
	}
	if (node->io_list && node->io_list->value)
	{
		check_expandable_vars(node->minishell, &node->io_list->value);
		check_wildcard(&node->io_list->value, &node->io_list->expanded_arg);
	}
}