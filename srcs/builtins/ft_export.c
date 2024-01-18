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
- quotes: single quotes nested inside double quotes will fail, and vice versa
	(eg. export tes't"t1't2'=43"56'
	bash: export: `test"t1t2=43"56': not a valid identifier)
- multiple arguments: each argument is stored as a separate variable
- if 1 argument fails, export moves on to the next arg*/
int	print_export(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		printf("declare -x %s\n", data->envp[i]);
		i++;
	}
	return (1);
}

int	check_valid_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		return (export_error(arg, EXPORT_OPTION));
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (export_error(arg, EXPORT_IDENTIFIER));
	return (1);
}

int	ft_export(t_data *data, t_command *current)
{
	char	*var_name;
	int		i;

	if (!current->argv[1])
		return (print_export(data));
	i = 1;
	while (current->argv[i])
	{
		remove_quotes(&current->argv[i]);
		var_name = extract_var_name(current->argv[i]);
		if (check_valid_arg(current->argv[i]))
		{
			printf("valid arg: %s\nvar name: %s\n",
				current->argv[i], var_name);
			update_envp(data, var_name, current->argv[i], "export");
		}
		free(var_name);
		i++;
	}
	printf("\n\n\n");
	ft_env(data);
	return (1);
}
