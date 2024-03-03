/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:28:53 by agan              #+#    #+#             */
/*   Updated: 2024/02/07 17:28:54 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Cleans str token after redir and appends args to node->value */
void	redir_clean(t_minishell *minishell, t_node *node)
{
	char	*str;

	str = node->value;
	node->value = ft_strjoin(node->value, " ");
	free (str);
	str = node->value;
	node->value = ft_strjoin (node->value, minishell->curr_token->value);
	free (str);
	ft_next_token(minishell);
}

/* Redirect helper function -> loops through redirects 
- Sets heredoc if found
- Appends to io node linked list */
t_node	*parser_redir(t_minishell *minishell, t_node *node)
{
	while (minishell->curr_token && is_redir(minishell->curr_token))
	{
		if (minishell->curr_token->type == T_HEREDOC)
			node->is_heredoc++;
		if (!new_io_node(minishell, node, &(node->io_list)))
			return (NULL);
		if (minishell->curr_token && minishell->curr_token->type == T_STRING)
			redir_clean(minishell, node);
	}
	return (node);
}

/* Redirect helper function 
- If redirect found before cmd, gets current cmd
- Creates new node with cmd values 
- Runs parser redir to append io nodes */
t_node	*ft_redir_helper(t_minishell *minishell, t_node **node)
{
	t_token	*curr_cmd;

	curr_cmd = get_curr_cmd(minishell);
	if (!curr_cmd)
		*node = ft_new_node("NULL", T_NULL, minishell);
	else
		*node = ft_new_node(curr_cmd->value, curr_cmd->type, minishell);
	if (!*node)
		return (NULL);
	if (curr_cmd)
		remove_node(curr_cmd);
	if (!parser_redir(minishell, *node))
		return (NULL);
	return (*node);
}
