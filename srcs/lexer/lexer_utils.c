/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:05:08 by agan              #+#    #+#             */
/*   Updated: 2024/01/15 16:05:09 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Print token list - TESTING
void print_token_list(t_token *token_list)
{
	while(token_list)
	{
		printf("%s\n", token_list->value);
		printf("%i\n", token_list->type);
		token_list = token_list->next;
	}
}

// Free tokens list and malloc'ed string
void ft_free_token_list(t_token **lst)
{
	t_token *tmp;
	t_token *next;

	tmp = *lst;
	if (!tmp)
		return ;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*lst = NULL;
}

// Create node
t_token *create_node(char *content, t_token_type type)
{
	t_token *node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = content;
	node->type = type;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_token	*token_last(t_token *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

// Lst add back function
void token_add_back(t_token **token_list, t_token *new)
{
	t_token *last;

	if (!new)
		return ;
	else if (!*token_list)
	{
		*token_list = new;
		return ;
	}
	last = token_last(*token_list);
	last->next = new;
	new->prev = last;
}

