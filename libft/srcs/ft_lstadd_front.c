/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:42:44 by yliew             #+#    #+#             */
/*   Updated: 2023/09/11 15:04:19 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	else if (lst)
		new->next = *lst;
	*lst = new;
}
/*
int	main(void)
{
	t_list  *lst1 = ft_lstnew("testing");
	t_list  *lst2 = ft_lstnew("aaaakjdksh");
	t_list  *new = ft_lstnew("hello world");
	t_list  *head;
	t_list  *temp;

	head = lst1;
	lst1->next = lst2;
	printf("Original list: %s, %s\nNew node:      %s\n",
		(char *)lst1->content, (char *)lst1->next->content,
		(char *) new->content);
	ft_lstadd_front(&head, new);
	printf("New list:      ");
	temp = head;
	while (temp)
	{
		if (temp->next)
			printf("%s, ", (char *)temp->content);
		else
			printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	return (0);
}
*/
