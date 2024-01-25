/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:42:55 by agan              #+#    #+#             */
/*   Updated: 2024/01/25 16:42:55 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
