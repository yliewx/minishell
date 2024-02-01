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

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	char	*command;

	if (argc > 1 && argv)
	{
		ft_putstr_fd("Program does not accept arguments.\n", 2);
		return (0);
	}
	array_dup(&minishell, envp);
	minishell.env_path = get_env_path(envp);
	//testing
	minishell.exit_status = 0;
	init_signals(&minishell);
	while (1)
	{
		command = readline("Minishell:~$ ");
		if (!command)
			return (printf("exit\n"), 1);
		if (command && command[0])
		{
			add_history(command);
			minishell.tokens = ft_lexer(command);
			minishell.curr_token = minishell.tokens;
			ft_parser(&minishell);
			ft_exec(&minishell);
			free(command);
		}
	}
	return (0);
}
