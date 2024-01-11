/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:42:44 by yliew             #+#    #+#             */
/*   Updated: 2023/09/11 11:39:12 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
static void	ft_printlist(t_list *lst)
{
	printf("List: ");
	while (lst)
	{
		if (lst->next)
			printf("%s, ", (char *)lst->content);
		else
			printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}

int main(void)
{
	t_list  *lst1 = ft_lstnew("lorem");
	t_list  *lst2 = ft_lstnew("ipsum");
	t_list  *lst3 = ft_lstnew("dolor sit amet");
	t_list  *lst4 = ft_lstnew("consectetur");
	t_list  *lst5 = ft_lstnew("adipiscing elit.");
	t_list  *lst6 = ft_lstnew(NULL);
	t_list  *temp;

	lst1->next = lst2;
	lst2->next = lst3;
	lst3->next = lst4;
	lst4->next = lst5;
	printf("List: ");
	ft_printlist(lst1);
	temp = ft_lstlast(lst1);
	printf("Last node in list: %s\n", (char *)temp->content);
	ft_printlist(lst6);
	temp = ft_lstlast(lst6);
	printf("Last node in list: %s\n", (char *)temp->content);
	return (0);
}
*/
