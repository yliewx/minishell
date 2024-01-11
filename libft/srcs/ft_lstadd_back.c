/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:42:44 by yliew             #+#    #+#             */
/*   Updated: 2023/09/11 11:43:32 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new)
		return ;
	else if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}
/*
static void	ft_printlist(t_list *lst)
{
	printf("New list:      ");
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
	t_list	*lst1 = ft_lstnew("testing");
	t_list	*lst2 = ft_lstnew("aaaakjdksh");
	t_list	*new = ft_lstnew("hello world");
	t_list	*head;

	head = lst1;
	lst1->next = lst2;
	printf("Original list: %s, %s\nNew node:      %s\n",
		(char *)lst1->content, (char *)lst1->next->content,
		(char *) new->content);
	ft_lstadd_back(&head, new);
	ft_printlist(head);
	head = NULL;
	printf("Original list: %s\nNew node:      %s\n",
		(char *)head, (char *) new->content);
	ft_lstadd_back(&head, new);
	ft_printlist(head);
	return (0);
}
*/
