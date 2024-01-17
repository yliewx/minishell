/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:58:48 by yliew             #+#    #+#             */
/*   Updated: 2024/01/17 17:58:54 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*no need to handle unclosed quotes; remove all paired quotes
(excluding single quotes that are nested inside double quotes & vice versa)*/
void	remove_quotes(char **arg)
{
	char	*new_str;
	int	in_quote;
	int	i;
	int	j;

	if (!ft_strchr(*arg, '\'') && !ft_strchr(*arg, '\"'))
		return ;
	new_str = malloc(ft_strlen(*arg) * sizeof(char));
	in_quote = 0;
	i = 0;
	j = 0;
	while ((*arg)[i])
	{
		if (((*arg)[i] == '\'' || (*arg)[i] == '\"') && in_quote == 0)
			in_quote = (*arg)[i++];
		else if ((*arg)[i] == in_quote)
		{
			in_quote = 0;
			i++;
		}
		new_str[j++] = (*arg)[i++];
	}
	new_str[j] = '\0';
	free(*arg);
	*arg = new_str;
}
