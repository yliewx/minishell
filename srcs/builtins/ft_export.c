/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:32:58 by yliew             #+s#    #+#            */
/*   Updated: 2024/01/11 17:33:05 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to print list of exported environment variables
- Sorts envp in alphabetical order befpre printing */
int	print_export(t_minishell *minishell)
{
	char	*var_name;
	char	*value;
	int		i;

	i = -1;
	if (!minishell->envp)
		return (set_exit_success(minishell));
	sort_envp(minishell->envp, 0, minishell->envp_size - 1);
	while (minishell->envp[++i])
	{
		var_name = extract_var_name(minishell->envp[i]);
		if (var_name && ft_strncmp(var_name, "_=", 3) != 0)
		{
			printf("declare -x %s", var_name);
			value = after_equal_sign(minishell->envp[i]);
			if (value[0])
				printf("\"%s\"", value);
			else
				free(value);
			printf("\n");
		}
		free(var_name);
	}
	return (set_exit_success(minishell));
}

/* Function to check whether the argument to export is valid
- Returns error if there is an option passed to export
- Returns error if the variable name contains invalid characters */
static int	check_valid_arg(char *arg, char *var_name, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		return (export_error(EXPORT_OPTION_ERR, arg, minishell));
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (export_error(EXPORT_ID_ERR, arg, minishell));
	i++;
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_'
			&& var_name[i] != '=')
			return (export_error(EXPORT_ID_ERR, arg, minishell));
		i++;
	}
	return (1);
}

/* Function to set environment variables
- Each argument is interpreted as a separate variable
- Checks for syntax errors in variable name before setting its value in envp
- If 1 argument fails, export sets an error and moves on to the next arg */
int	ft_export(t_minishell *minishell, t_node *node)
{
	char	*var_name;
	int		i;

	if (!node->expanded_arg[1])
		return (print_export(minishell));
	i = 1;
	while (node->expanded_arg[i])
	{
		var_name = extract_var_name(node->expanded_arg[i]);
		if (check_valid_arg(node->expanded_arg[i], var_name, minishell))
		{
			if (update_envp(minishell, var_name, node->expanded_arg[i],
					"export") == -1)
				return (minishell->exit_status);
		}
		free(var_name);
		i++;
	}
	if (minishell->minishell_err != NO_ERR)
		return (minishell->exit_status);
	return (set_exit_success(minishell));
}
