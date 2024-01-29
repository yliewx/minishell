/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:44:38 by yliew             #+#    #+#             */
/*   Updated: 2024/01/11 15:46:40 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
/*
void	make_test_nodes(t_node **node)
{
	(*node) = malloc(sizeof(t_node));
	(*node)->type = T_AND;
	(*node)->value = "&&";
	(*node)->left = malloc(sizeof(t_node));
	(*node)->left->type = T_STRING;
	(*node)->left->value = "export test=123";
	(*node)->right = malloc(sizeof(t_node));
	(*node)->right->type = T_STRING;
	(*node)->right->value = "env";
}
*/
int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	//char	*command;

	if (argc > 1 && argv)
	{
		ft_putstr_fd("Program does not accept arguments.\n", 2);
		return (0);
	}
	array_dup(&minishell, envp);
	//testing
	/*minishell.command_list = malloc(sizeof(t_command));
	minishell.command_list->minishell = &minishell;
	minishell.minishell->exit_status = 0;
	init_signals(&minishell);
	while (1)
	{
		command = readline("minishell$ ");
		if (!command)
			return (printf("exit\n"), 1);
		else if (command && command[0])
		{
			add_history(command);
			minishell.command_list->argv = ft_split_argv(command);
			//make_test_nodes(&minishell.ast);
			if (minishell.command_list->argv)
			{
				int	i = 0;
				while (minishell.command_list->argv[i])
				{
					printf("command[%i]: %s\n", i, minishell.command_list->argv[i]);
					i++;
				}
				//begin_execution(&minishell, minishell.ast);
				if (!check_builtin(&minishell, minishell.command_list))
					printf("command is not a builtin\n");
			}
		}
	}*/
	return (0);
}