/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:57:57 by agan              #+#    #+#             */
/*   Updated: 2024/01/25 16:57:57 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to create string token
Looks for end of string
Creates new node with malloc-ed string
Adds node to token_list */
t_token **create_str_token(t_token **token_list, char *line, int i, int j)
{
	t_token *token;
	char *str;
	int end;

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
	token_add_back(token_list, token);
	return(token_list);
}

/* Function to find the next token (symbol or string) */
int find_next_token(t_minishell *minishell, t_token **token_list, char *line, int *i)
{
	int j;

	j = 0;
	while (line[*i] && !is_symbol(line[*i]))
	{
		j++;
		(*i)++;
	}
	if (is_symbol(line[*i]) && j == 0)
	{
		if (!sym_handler(minishell, token_list, line, i))
			return (-1);
	}
	else
	{
		if (!create_str_token(token_list, line, *i, j))
			return (-1);
	}
	return (*i);
}

/* Function to check for unclosed quote in values within token_list */
int quotes_checker(t_token *token_list)
{
	t_token *lst;
	int i;
	char *end_quote;

	lst = token_list;
	while (lst)
	{
		i = -1;
		if (lst->value)
		{
			while (lst->value[++i])
			{
				if (lst->value[i] == '\'' || lst->value[i] == '\"')
				{
					if (lst->value[i] == '\'')
						end_quote = ft_strrchr(&lst->value[i], '\'');
					else if (lst->value[i] == '\"')
						end_quote = ft_strrchr(&lst->value[i], '\"');
					if (end_quote == &(lst->value[i]))
					{
						ft_putstr_fd("Error: Unclosed quote found in: ", 2);
						ft_putstr_fd(lst->value, 2);
						ft_putstr_fd("\n", 2);
						return (-1);
					}
					else
						i = end_quote - lst->value;
				}
			}
		}
		lst = lst->next;
	}
	return (0);
}