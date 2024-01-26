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
int	print_export(t_data *data)
{
	char	*var_name;
	int		i;

	i = 0;
	sort_envp(data->envp, 0, data->envp_size - 1);
	while (data->envp[i])
	{
		var_name = extract_var_name(data->envp[i]);
		if (ft_strncmp(var_name, "_=", 3) != 0)
		{
			printf("declare -x %s\"%s\"\n", var_name,
				after_equal_sign(data->envp[i]));
		}
		free(var_name);
		i++;
	}
	return (1);
}

static int	check_valid_arg(char *arg, char *var_name)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		return (export_error(arg, EXPORT_OPTION));
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (export_error(arg, EXPORT_IDENTIFIER));
	i++;
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_'
			&& var_name[i] != '=')
			return (export_error(arg, EXPORT_IDENTIFIER));
		i++;
	}
	return (1);
}

int	ft_export(t_data *data, t_command *current)
{
	char	*var_name;
	//char	*temp;
	int		i;

	if (!current->argv[1])
		return (print_export(data));
	i = 1;
	while (current->argv[i])
	{
		remove_quotes(&current->argv[i]);
		var_name = extract_var_name(current->argv[i]);
		printf("extracted var_name: %s\n", var_name);
		if (check_valid_arg(current->argv[i], var_name))
			update_envp(data, var_name, current->argv[i], "export");
		free(var_name);
		i++;
	}
	return (1);
}
