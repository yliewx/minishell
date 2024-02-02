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

// t_token **create_str_token(t_token **token_list, char *line, int i, int j)
// {
// 	t_token *token;
// 	char *str;
// 	int end;

// 	end = i;
// 	str = malloc(sizeof(char) * (i - j + 1));
// 	if (!str)
// 		return (NULL);
// 	while (line[end - 1] == ' ')
// 		end--;
// 	ft_strlcpy(str, &line[i - j], end - (i - j) + 1);
// 	token = create_node(str, T_STRING);
// 	if (!token)
// 		return (free(str), NULL);
// 	token_add_back(token_list, token);
// 	return(token_list);
// }

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

t_token **create_symbol(t_token **token_list, t_token_type sym_type, int *i)
{
	t_token *token;

	token = create_node(NULL, sym_type);
	if (!token)
		return (NULL);
	token_add_back(token_list, token);
	if (sym_type == T_OR || sym_type == T_AND || sym_type == T_APPEND || sym_type == T_HEREDOC)
		*i += 2;
	else
		*i += 1;
	return (token_list);
}

t_token **create_sym_token(t_token **token_list, char *line, int *i)
{

	if (!ft_strncmp(line + *i, "||", 2))
		return (create_symbol(token_list, T_OR, i));
	else if (!ft_strncmp(line + *i, "|", 1))
		return (create_symbol(token_list, T_PIPE, i));
	else if (!ft_strncmp(line + *i, ">>", 2))
		return (create_symbol(token_list, T_APPEND, i));
	else if (!ft_strncmp(line + *i, "<<", 2))
		return (create_symbol(token_list, T_HEREDOC, i));
	else if (!ft_strncmp(line + *i, "&&", 2))
		return (create_symbol(token_list, T_AND, i));
	else if (!ft_strncmp(line + *i, "<", 1))
		return (create_symbol(token_list, T_REDIR_L, i));
	else if (!ft_strncmp(line + *i, ">", 1))
		return (create_symbol(token_list, T_REDIR_R, i));
	else if (!ft_strncmp(line + *i, "(", 1))
		return (create_symbol(token_list, T_OPEN, i));
	else if (!ft_strncmp(line + *i, ")", 1))
		return (create_symbol(token_list, T_CLOSE, i));
	else
	{
		write(2, "invalid syntax\n", 15);
		return (NULL);
	}
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
	{
		if (!create_str_token(token_list, line, *i, j))
			return (-1);
	}
	return (*i);
}