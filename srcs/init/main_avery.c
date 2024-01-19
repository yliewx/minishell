/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_avery.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:05:26 by agan              #+#    #+#             */
/*   Updated: 2024/01/12 18:05:28 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // Lexer main
// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	data;

// 	if (argc > 1 && argv)
// 	{
// 		ft_putstr_fd("Program does not accept arguments.\n", 2);
// 		return (0);
// 	}
// 	array_dup(&data, envp);
// 	//testing
// 	data.history_list = malloc(sizeof(t_history));
// 	data.history_list->input = readline("Minishell:~$ ");
//     while (ft_strlen(data.history_list->input) == 0)
//     {
//         data.history_list->input = readline("Minishell:~$ ");
//     }
// 	return (0);
// }

// // Testing main linked list functions
// int main(void)
// {
// 	t_token *node;
// 	t_token *token_list;
// 	token_list = NULL;
// 	char *s1 = "first string";
// 	char *s2 = "second string";

// 	node = create_node(s1);
// 	token_add_back(&token_list, node);
// 	node = create_node (s2);
// 	token_add_back(&token_list, node);
// 	print_token_list(token_list);
// }

// Lexer main
int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 1 && argv)
	{
		ft_putstr_fd("Program does not accept arguments.\n", 2);
		return (0);
	}
	array_dup(&data, envp);
	//testing
	data.history_list = malloc(sizeof(t_history));
	data.history_list->input = readline("Minishell:~$ ");
	ft_lexer(data.history_list->input);
	return (0);
}
