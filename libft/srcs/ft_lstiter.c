/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:42:44 by yliew             #+#    #+#             */
/*   Updated: 2023/09/11 13:58:55 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	if (!lst || !f)
		return ;
	temp = lst;
	while (temp)
	{
		f(temp->content);
		temp = temp->next;
	}
}
/*
static void	test_revcase(void *s)
{
	char	*content;
	int		i;

	content = (char *)s;
	i = 0;
	while (content[i])
	{
		if (content[i] >= 'a' && content[i] <= 'z')
			content[i++] -= 32;
		else if (content[i] >= 'A' && content[i] <= 'Z')
			content[i++] += 32;
		else
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
	t_list  *lst1 = ft_lstnew(strdup("Lorem"));
	t_list  *lst2 = ft_lstnew(strdup("ipsuM"));
	t_list  *lst3 = ft_lstnew(strdup("Dolor siT Amet"));
	t_list  *lst4 = ft_lstnew(strdup("conectetR"));
	t_list  *lst5 = ft_lstnew(strdup("Adipiscing eliT."));

	lst1->next = lst2;
	lst2->next = lst3;
	lst3->next = lst4;
	lst4->next = lst5;
	ft_printlist(lst1);
	ft_lstiter(lst1, test_revcase);
	ft_printlist(lst1);
	return (0);
}
*/
