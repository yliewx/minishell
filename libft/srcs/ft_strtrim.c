/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:13:57 by yliew             #+#    #+#             */
/*   Updated: 2023/09/13 16:48:34 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	size_t	start;
	size_t	end;

	dst = 0;
	start = 0;
	if (!s1 || !set)
		return ((char *)s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > start)
		end--;
	dst = ft_substr(s1, start, end - start);
	return (dst);
}
/*
int	main(void)
{
	char	str1[] = "  +-/Hello World , ---+ ";
	char	str2[] = "Hello World ";
	char	str3[] = "lorem \n ipsum \t dolor \n sit \t amet ";
	char	str4[] = "          ";
	char	*str5 = calloc(10, sizeof(char));
	char	set[] = " +-/";

	printf("Str1:       '%s'\nTrim:       '%s'\nAfter trim: '%s'\n\n",
		str1, set, ft_strtrim(str1, set));
	printf("Str2:       '%s'\nTrim:       '%s'\nAfter trim: '%s'\n\n",
		str2, "", ft_strtrim(str2, ""));
	printf("Str3:       '%s'\nTrim:       '%s'\nAfter trim: '%s'\n",
		str3, " ", ft_strtrim(str3, " "));
	printf("Str4:       '%s'\nTrim:       '%s'\nAfter trim: '%s'\n\n",
		str4, " ", ft_strtrim(str4, " "));
	printf("Str5:       '%s'\nTrim:       '%s'\nAfter trim: '%s'\n\n",
		str5, " ", ft_strtrim(str5, " "));
	printf("Str6:       '%s'\nTrim:       '%s'\nAfter trim: '%s'\n\n",
		"", "", ft_strtrim("", ""));
	return (0);
}
*/
