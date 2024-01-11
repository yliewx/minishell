/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:42:44 by yliew             #+#    #+#             */
/*   Updated: 2023/09/11 11:30:28 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
/*
int	main(void)
{
	t_list	*lst1 = ft_lstnew("lorem");
	t_list	*lst2 = ft_lstnew("ipsum");
	t_list	*lst3 = ft_lstnew("dolor sit amet");
	t_list	*lst4 = ft_lstnew("consectetur");
	t_list	*lst5 = ft_lstnew("adipiscing elit.");
	t_list	*temp = lst1;

	lst1->next = lst2;
	lst2->next = lst3;
	lst3->next = lst4;
	lst4->next = lst5;
	while (temp)
	{
		if (temp->next)
			printf("%s, ", (char *)temp->content);
		else
			printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	printf("No. of nodes in list: %i\n", ft_lstsize(lst1));
	return (0);
}
*/
