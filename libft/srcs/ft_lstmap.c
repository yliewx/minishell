/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:42:44 by yliew             #+#    #+#             */
/*   Updated: 2023/09/14 15:38:48 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new_node;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			if (new_content)
				del(new_content);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, new_node);
		lst = lst->next;
	}
	return (head);
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

static void	*test_revcase(void *s)
{
	char	*content;
	int		i;

	content = ft_strdup((char *)s);
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
	return (content);
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
	t_list	*newlst;

	lst1->next = lst2;
	lst2->next = lst3;
	lst3->next = lst4;
	lst4->next = lst5;
	ft_printlist(lst1);
	newlst = ft_lstmap(lst1, test_revcase, ft_del);
	ft_printlist(newlst);
	newlst = ft_lstmap(NULL, test_revcase, ft_del);
	ft_printlist(newlst);
	printf("\n");
	newlst = ft_lstmap(lst1, NULL, ft_del);
	ft_printlist(newlst);
	return (0);
}
*/
