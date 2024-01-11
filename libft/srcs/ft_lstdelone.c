/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:42:44 by yliew             #+#    #+#             */
/*   Updated: 2023/09/11 11:54:08 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
	lst = NULL;
}
/*
static void	ft_del(void *s)
{
	char	*str;
        size_t	i;
	size_t	n;

	str = (char *)s;
	i = 0;
	n = ft_strlen(str);
	while (str[i] && i < n)
	{
		str[i] = '\0';
		i++;
	}
}

int	main(void)
{
	t_list	*lst1 = ft_lstnew("hello world");
	t_list	*lst2 = ft_lstnew("testing");

	lst2->next = lst1;
	printf("Original list: %s, %s\n", (char *)lst2->content,
		(char *)lst2->next->content);
	ft_lstdelone(lst1, ft_del);
	return (0);
}
*/
