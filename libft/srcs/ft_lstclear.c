/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:42:44 by yliew             #+#    #+#             */
/*   Updated: 2023/09/11 13:26:48 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!*lst || !del)
		return ;
	temp = NULL;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}
/*
static void	ft_del(void *s)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
}

static void	ft_printlist(t_list *lst)
{
	printf("List:      ");
	while (lst)
	{
		if (lst->next)
			printf("%s, ", (char *)lst->content);
		else
			printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}

int	main(void)
{
	t_list	*lst1 = ft_lstnew("lorem");
	t_list	*lst2 = ft_lstnew("ipsum");
	t_list	*lst3 = ft_lstnew("dolor sit amet");
	t_list	*lst4 = ft_lstnew("consectetur");
	t_list	*lst5 = ft_lstnew("adipiscing elit.");

	lst1->next = lst2;
	lst2->next = lst3;
	lst3->next = lst4;
	lst4->next = lst5;
	ft_printlist(lst1);
	ft_lstclear(&lst1, ft_del);
	ft_printlist(lst1);
	return (0);
}
*/
