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

int ft_minishell(t_minishell *minishell)
{
	char *command;

	while (1)
	{
		command = ft_cmd_line(minishell->user);
		if (!command)
			return (printf("exit\n"), 1);
		if (command && command[0])
		{
			add_history(command);
			minishell->tokens = ft_lexer(command);
			if (minishell->tokens)
			{
				minishell->curr_token = minishell->tokens;
				ft_parser(minishell);
				ft_exec(minishell);
			}
			dup2(minishell->old_stdin, STDIN_FILENO);
			free(command);
		}
	}
	close(minishell->old_stdin);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_minishell minishell;

	if (arg_checker(argc, argv) == -1)
		return (1);
	init_env(&minishell, envp);
	init_minishell(&minishell);
	ft_minishell(&minishell);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_minishell	minishell;
// 	char	*command;
// 	int old_stdin;
// 	char *user;

// 	command = NULL;
// 	if (argc > 1 && argv)
// 	{
// 		ft_putstr_fd("Program does not accept arguments.\n", 2);
// 		return (0);
// 	}
// 	envp_dup(&minishell, envp);
// 	minishell.env_path = get_env_path(envp);
// 	//testing
// 	minishell.exit_status = 0;
// 	init_signals(&minishell);
// 	old_stdin = dup(STDIN_FILENO);
// 	user = value_in_env(minishell.envp, "USER", 4);
// 	while (1)
// 	{
// 		ft_putstr_fd(user, 1);
// 		ft_putstr_fd("@", 1);
// 		minishell.heredoc_count = 0;
// 		minishell.heredoc_list = NULL;
// 		command = readline("minishell:~$ ");
// 		if (!command)
// 			return (printf("exit\n"), 1);
// 		if (command && command[0])
// 		{
// 			add_history(command);
// 			minishell.tokens = ft_lexer(command);
// 			if (minishell.tokens)
// 			{
// 				minishell.curr_token = minishell.tokens;
// 				ft_parser(&minishell);
// 				//print_heredoc(minishell.heredoc_list);
// 				ft_exec(&minishell);
// 			}
// 				dup2(old_stdin, STDIN_FILENO);
// 				free(command);
// 		}
// 	}
// 	close(old_stdin);
// 	return (0);
// }
