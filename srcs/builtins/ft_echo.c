/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:30:05 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 17:31:35 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flag_counter(t_node *node)
{
	int	i;
	int	count;

	count = 0;
	i = 1;
	if (node->expanded_arg[1])
	{
		while (node->expanded_arg[i])
		{
			if (ft_strncmp(node->expanded_arg[i], "-n", 3) == 0)
				count++;
			else if (ft_strncmp(node->expanded_arg[i], "-n", 3))
				break ;
			i++;
		}
	}
	return (count);
}

/* Function to display a line of text
- Omits newline character if the -n option is present */
int	ft_echo(t_node *node)
{
	bool	omit_newline;
	int		flag;
	int		i;

	omit_newline = 0;
	flag = flag_counter(node);
	if (flag > 0)
		omit_newline = 1;
	i = flag + 1;
	if (node->expanded_arg[i])
	{
		while (node->expanded_arg[i])
		{
			if (ft_strlen(node->expanded_arg[i]) > 0)
			{
				printf("%s", node->expanded_arg[i]);
				if (node->expanded_arg[i + 1])
					printf(" ");
			}
			i++;
		}
	}
	if (!omit_newline)
		printf("\n");
	return (set_exit_success(node->minishell));
}

/*#include "minishell.h"

bool	check_echo_option(t_node *node, int *i)
{
	if (!node->expanded_arg[1])
		return (false);
	while (node->expanded_arg[*i]
		&& (ft_strncmp(node->expanded_arg[*i], "-n", 3) == 0))
		(*i)++;
	if (*i != 1)
		return (true);
	return (false);
}
int	ft_echo(t_node *node)
{
	bool	omit_newline;
	int		i;

	i = 1;
	omit_newline = check_echo_option(node, &i);
	printf("i: %i\n", i);
	printf("arg: %s\n", node->expanded_arg[i]);
	if (node->expanded_arg[1])
	{
		while (node->expanded_arg[i])
		{
			if (ft_strlen(node->expanded_arg[i]) > 0)
			{
				printf("%s", node->expanded_arg[i]);
				if (node->expanded_arg[i + 1])
					printf(" ");
			}
			i++;
		}
	}
	if (!omit_newline)
		printf("\n");
	return (set_exit_success(node->minishell));
}*/
