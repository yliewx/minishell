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
// 	data.command_list = malloc(sizeof(t_command));
// 	data.command_list->data = &data;
// 	data.command_list->command = readline("Test command: ");
// 	data.command_list->flags = readline("Test flags: ");
// 	if (ft_strlen(data.command_list->flags) == 0)
// 	{
// 		free(data.command_list->flags);
// 		data.command_list->flags = NULL;
// 	}
// 	data.command_list->arg = readline("Test arg: ");
// 	if (ft_strlen(data.command_list->arg) == 0)
// 	{
// 		free(data.command_list->arg);
// 		data.command_list->arg = NULL;
// 	}
// 	if (data.command_list->command)
// 	{
// 		if (!check_builtin(&data, data.command_list))
// 			printf("command is not a builtin\n");
// 	}
// 	return (0);
// }

