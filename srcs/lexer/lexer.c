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

// Checks if is symbol
int is_symbol(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')')
		return (1);
	return (0);
}

t_token **create_str_token(t_token **token_list, char *line, int i, int j)
{
	t_token *token;
	char *str;
	int end;

	end = i;
	str = malloc(sizeof(char) * (i - j + 1));
	if (!str)
		return (NULL);
	while (line[end - 1] == ' ')
		end--;
	ft_strlcpy(str, &line[i - j], end - (i - j) + 1);
	token = create_node(str, T_STRING);
	if (!token)
		return (free(str), NULL);
	token_add_back(token_list, token);
	return(token_list);
}

t_token **create_symbol(t_token **token_list, t_token_type sym_type, int *i)
{
	t_token *token;

	token = create_node(NULL, sym_type);
	if (!token)
		return (NULL);
	token_add_back(token_list, token);
	if (sym_type == T_PIPE || sym_type == T_AND || sym_type == T_APPEND || sym_type == T_HEREDOC)
		*i += 2;
	else
		*i += 1;
	return (token_list);
}

t_token **create_sym_token(t_token **token_list, char *line, int *i)
{
	if (!ft_strncmp(line + *i, "|", 1))
		create_symbol(token_list, T_PIPE, i);
	else if (!ft_strncmp(line + *i, "||", 2))
		create_symbol(token_list, T_OR, i);
	else if (!ft_strncmp(line + *i, "<<", 2))
		create_symbol(token_list, T_APPEND, i);
	else if (!ft_strncmp(line + *i, ">>", 2))
		create_symbol(token_list, T_HEREDOC, i);
	else if (!ft_strncmp(line + *i, "&&", 2))
		create_symbol(token_list, T_AND, i);
	else if (!ft_strncmp(line + *i, "<", 1))
		create_symbol(token_list, T_REDIR_L, i);
	else if (!ft_strncmp(line + *i, ">", 1))
		create_symbol(token_list, T_REDIR_R, i);
	else if (!ft_strncmp(line + *i, "(", 1))
		create_symbol(token_list, T_OPEN, i);
	else if (!ft_strncmp(line + *i, ")", 1))
		create_symbol(token_list, T_CLOSE, i);
	else
	{
		write(2, "invalid syntax\n", 15);
		return (NULL);
	}
	return (token_list);
}

int find_next_token(t_token **token_list, char *line, int *i)
{
	int j;

	j = 0;
	(void)token_list;
	while (line[*i] && !is_symbol(line[*i]))
	{
		j++;
		(*i)++;
	}
	if (is_symbol(line[*i]) && j == 0)
	{
		if (!create_sym_token(token_list, line, i))
			return (-1);
	}
	else
		create_str_token(token_list, line, *i, j);
	return (*i);
}

void skip_spaces(char *line, int *i)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
}

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
			break ;
	}
	//print_token_list(token_list);
	return (token_list);
}