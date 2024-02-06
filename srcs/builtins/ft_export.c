/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:32:58 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 17:33:05 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*there cannot be spaces before/after the equal sign
eg. export testvar = 123, export testvar= 123, export "testvar = 123"
should all give syntax error
but export "testvar= 123" succeeds
- no need to handle unclosed quotes
- multiple arguments: each argument is stored as a separate variable
- if 1 argument fails, export moves on to the next arg*/
int	print_export(t_minishell *minishell)
{
	char	*var_name;
	char	*value;
	int		i;

	i = 0;
	if (!minishell->envp)
		return (set_exit_success(minishell));
	sort_envp(minishell->envp, 0, minishell->envp_size - 1);
	while (minishell->envp[i])
	{
		var_name = extract_var_name(minishell->envp[i]);
		if (var_name && ft_strncmp(var_name, "_=", 3) != 0)
		{
			printf("declare -x %s", var_name);
			value = after_equal_sign(minishell->envp[i]);
			if (value[0])
				printf("\"%s\"\n", value);
			else
			{
				free(value);
				printf("\n");
			}
		}
		free(var_name);
		i++;
	}
	return (set_exit_success(minishell));
}

static int	check_valid_arg(char *arg, char *var_name, t_minishell *minishell)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		return (export_error(EXPORT_OPTION, arg, minishell));
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (export_error(EXPORT_IDENTIFIER, arg, minishell));
	i++;
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_'
			&& var_name[i] != '=')
			return (export_error(EXPORT_IDENTIFIER, arg, minishell));
		i++;
	}
	return (1);
}

int	ft_export(t_minishell *minishell, t_node *node)
{
	char	*var_name;
	int		last_valid_arg;
	int		i;

	if (!node->expanded_arg[1])
		return (print_export(minishell));
	i = 1;
	last_valid_arg = -1;
	while (node->expanded_arg[i])
	{
		remove_quotes(&node->expanded_arg[i]);
		var_name = extract_var_name(node->expanded_arg[i]);
		if (check_valid_arg(node->expanded_arg[i], var_name, minishell))
		{
			update_envp(minishell, var_name, node->expanded_arg[i], "export");
			last_valid_arg = i;
		}
		free(var_name);
		i++;
	}
	if (last_valid_arg != i - 1)
		return (1);
	return (set_exit_success(minishell));
}
