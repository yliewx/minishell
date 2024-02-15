/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:39:50 by agan              #+#    #+#             */
/*   Updated: 2024/02/06 15:39:51 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to create string token
Looks for end of string
Creates new node with malloc-ed string
Adds node to token_list */
t_token	*create_str_token(t_minishell *minishell, char *line, int i, int j)
{
	t_token	*token;
	char	*str;
	int		end;

	end = i;
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	while (line[end - 1] == ' ')
		end--;
	ft_strlcpy(str, &line[i - j], j - (i - end) + 1);
	token = create_node(str, T_STRING);
	if (!token)
		return (free(str), NULL);
	token_add_back(&minishell->tokens, token);
	return (token);
}
