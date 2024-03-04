/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:17:42 by agan              #+#    #+#             */
/*   Updated: 2024/02/05 15:17:43 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_checker(int argc, char **argv)
{
	if (argc > 1 && argv)
	{
		ft_putstr_fd("Minishell does not accept arguments.\n", 2);
		return (-1);
	}
	return (0);
}

char	*ft_clean_cwd(t_minishell *minishell)
{
	char	*tmp_cwd;
	char	*tmp;
	char	*home;

	home = value_in_env(minishell->envp, "HOME");
	if (home)
	{
		tmp_cwd = getcwd(NULL, 0);
		tmp = tmp_cwd;
		tmp_cwd = ft_strdup(tmp_cwd + ft_strlen(home));
		free(tmp);
	}
	else
		tmp_cwd = getcwd(NULL, 0);
	return (tmp_cwd);
}

/* Function to create prompt str with $USER@Minishell:~$ */
void	ft_prompt(t_minishell *minishell)
{
	char	*tmp;
	char	*tmp_cwd;

	if (minishell->user)
		tmp = ft_strjoin(minishell->user, PROMPT_GREEN);
	else
		tmp = ft_strjoin("", PROMPT_GREEN_NO_USER);
	minishell->prompt = NULL;
	tmp_cwd = ft_clean_cwd(minishell);
	minishell->prompt = ft_strjoin(tmp, tmp_cwd);
	free(tmp);
	free(tmp_cwd);
	tmp_cwd = minishell->prompt;
	minishell->prompt = ft_strjoin(minishell->prompt, "$ ");
	free(tmp_cwd);
	tmp_cwd = minishell->prompt;
	minishell->prompt = ft_strjoin(minishell->prompt, RESET_PROMPT_COLOUR);
	if (tmp_cwd)
		free(tmp_cwd);
	if (!minishell->prompt)
	{
		print_str_err(MEM_ERR, NULL, minishell);
		return ;
	}
}

// /* Function to create prompt str with $USER@Minishell:~$ */
// void	ft_prompt(t_minishell *minishell)
// {
// 	char	*tmp;
// 	char	*tmp_cwd;

// 	if (minishell->user)
// 		tmp = ft_strjoin(minishell->user, "@Yash:\033[1;32m~");
// 	else
// 		tmp = ft_strjoin("", "Yash:\033[1;32m~");
// 	minishell->prompt = NULL;
// 	tmp_cwd = ft_clean_cwd(minishell);
// 	minishell->prompt = ft_strjoin(tmp, tmp_cwd);
// 	free(tmp);
// 	free(tmp_cwd);
// 	tmp_cwd = minishell->prompt;
// 	minishell->prompt = ft_strjoin(minishell->prompt, RESET_PROMPT_COLOR);
// 	free(tmp_cwd);
// 	if (!minishell->prompt)
// 	{
// 		print_str_err(MEM_ERR, NULL, minishell);
// 		return ;
// 	}
// }

char	*ft_readline(t_minishell *minishell)
{
	char	*command;

	if (minishell->prompt)
	{
		printf(PROMPT_CYAN);
		command = readline(minishell->prompt);
	}
	else
	{
		command = readline("Yash:~$ ");
	}
	return (command);
}
