/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:42:44 by yliew             #+#    #+#             */
/*   Updated: 2023/09/13 16:43:03 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

/*
int	main(void)
{
	t_list	*ptr;
	char	test1[] = "Lorem ipsum dolor sit amet. Sed non risus.";
	int		test2 = 42;

	ptr = ft_lstnew(test1);
	printf("Content: %s\n", (char *)ptr->content);
	printf("Next:    %s\n", (char *)ptr->next);
	ptr = ft_lstnew(&test2);
	printf("Content: %i\n", (*(int *)ptr->content));
	printf("Next:    %s\n", (char *)ptr->next);
	ptr = ft_lstnew(0);
	printf("Content: %s\n", (char *)ptr->content);
	printf("Next:    %s\n", (char *)ptr->next);
	return (0);
}
*/
