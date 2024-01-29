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
(excluding single quotes that are nested inside double quotes & vice versa)
export "abc"def'ghi''=xyz'l"mao"
export "abc"def'ghi''"=x"yz'l"mao" //will fail in bash export
export "abc'def'ghi=x"yzl"mao" //will fail in bash export; check echo
export "abc"def'ghi'"=xyz"l"mao"*/
void	remove_quotes(char **arg)
{
	char	*new_str;
	int		in_quote;
	int		i;
	int		j;
	int		len;

	if (!ft_strchr(*arg, '\'') && !ft_strchr(*arg, '\"'))
		return ;
	new_str = malloc(ft_strlen(*arg) * sizeof(char));
	i = 0;
	j = 0;
	while ((*arg)[i])
	{
		in_quote = 0;
		len = i;
		if (is_quote((*arg)[len]))
		{
			in_quote = (*arg)[len++];
			i++;
		}
		while ((in_quote != 0 && (*arg)[len] && (*arg)[len] != in_quote)
			|| (in_quote == 0 && (*arg)[len] && !is_quote((*arg)[len])))
			len++;
		while (i < len)
			new_str[j++] = (*arg)[i++];
		i++;
	}
	new_str[j] = '\0';
	free(*arg);
	*arg = new_str;
}