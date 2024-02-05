/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:55:56 by agan              #+#    #+#             */
/*   Updated: 2024/01/25 16:55:57 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function to init and create node */
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

/* Function to get last token */
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

/* Function to add node to back of list */
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
