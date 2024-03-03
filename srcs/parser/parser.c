/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:59:02 by agan              #+#    #+#             */
/*   Updated: 2024/01/22 13:59:03 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Recursive function to build ast 
- Gets left node
- Checks for binop and prec >= min prec -> get right node
- Combine left and right node to binop node
- Returns binop node or left */
t_node	*ft_ast(t_minishell *minishell, int min_prec)
{
	t_node			*left;
	t_node			*right;
	t_token			*op;

	left = ft_cmd(minishell);
	if (!left)
		return (NULL);
	while (minishell->curr_token && is_binop(minishell->curr_token) && \
		get_token_prec(minishell->curr_token) >= min_prec)
	{
		op = minishell->curr_token;
		ft_next_token(minishell);
		if (minishell->curr_token == NULL)
			return (set_exit_error(minishell, SYNTAX_ERR, 1), left);
		right = ft_ast(minishell, get_token_prec(op) + 1);
		if (!right)
			return (left);
		left = ft_combine(minishell, op->type, left, right);
		if (!left)
			return (NULL);
	}
	return (left);
}

// Parser to run prescedence climbing function
t_node	*ft_parser(t_minishell *minishell)
{
	if (minishell->curr_token)
		minishell->ast = ft_ast(minishell, 0);
	return (minishell->ast);
}
