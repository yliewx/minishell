/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:18:08 by agan              #+#    #+#             */
/*   Updated: 2024/01/11 19:18:09 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Runs lexer function on command
Iterates through command line
Skips spaces and finds next token to tokenize
After tokenization, runs quote checker to check for unclosed quotes
*/
t_token *ft_lexer(char *line)
{
	t_token *token_list;
	int i;

	i = 0;
	token_list = NULL;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (find_next_token(&token_list, line, &i) == -1)
		{
			ft_free_token_list(&token_list);
			break ;
		}
	}
	if (quotes_checker(token_list) == -1)
		ft_free_token_list(&token_list);
	//print_token_list(token_list);
	return (token_list);
}