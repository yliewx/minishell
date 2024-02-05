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

int	expand_exit_status(t_minishell *minishell, char **arg, int start)
{
	char	*new_str;
	char	*value;
	int		value_len;

	value = ft_itoa(minishell->exit_status);
	value_len = ft_strlen(value);
	new_str = replace_with_value(*arg, value, start,
		ft_strlen(*arg) - 2 + value_len);
	free(value);
	free(*arg);
	*arg = new_str;
	return (start + value_len);
}

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
	new_str = replace_with_value(*arg, value, var_start - *arg,
		ft_strlen(*arg) - var_len + ft_strlen(value));
	next_start_pos = var_start - *arg + ft_strlen(value);
	if (ft_strlen(value) == 0)
		free(value);
	free(var_name);
	free(*arg);
	*arg = new_str;
	return (next_start_pos);
}

int	ft_expand(t_minishell *minishell, char **arg, char *var_start)
{
	int		next_start_pos;

	next_start_pos = 0;
	if (var_start[1] == '?')
		next_start_pos = expand_exit_status(minishell, arg, var_start - *arg);
	else if (var_start[1] != ' ' && is_var_name(var_start[1]))
		next_start_pos = expand_var(minishell, arg, var_start);
	return (next_start_pos);
}

void	check_expandable_var(t_minishell *minishell, char **arg, char *var_start)
{
	int	next_start_pos;

	if (var_start)
		printf("\n\nvar_start 1: %s\n", var_start);
	printf("current arg: %s\n\n", *arg);
	if (!var_start || !var_start[0])
		return ;
	var_start = ft_strchr(var_start, '$');
	if (!var_start)
		return ;
	if (skip_quotes(var_start, *arg))
		var_start = get_end_quote(var_start + 1, '\'');
	printf("var_start 2: %s\n", var_start);
	while (var_start && var_start[1] && var_start[1] == '$')
		var_start++;
	if (var_start && var_start[0] == '$')
	{
		next_start_pos = ft_expand(minishell, arg, var_start);
		if (next_start_pos > 0)
			var_start = *arg + next_start_pos;
	}
	check_expandable_var(minishell, arg, var_start);
}

void	get_expanded_arg(t_node *node)
{
	if (node && node->value)
	{
		check_expandable_var(node->minishell, &node->value, node->value);
		check_wildcard(&node->value, &node->expanded);
		if (node->expanded)
			node->expanded_arg = ft_split_argv(node->expanded);
		else
			node->expanded_arg = ft_split_argv(node->value);
	}
	if (node->io_list && node->io_list->value)
	{
		check_expandable_var(node->minishell, &node->io_list->value,
			node->io_list->value);
		if (is_ambiguous_redir(node->io_list))
			expander_error(AMBIG_REDIR_ERR, node->io_list->value,
				node->minishell);
		else
			check_wildcard(&node->io_list->value, &node->io_list->expanded_arg);
	}
}