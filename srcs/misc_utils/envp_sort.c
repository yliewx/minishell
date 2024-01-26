/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:37:42 by yliew             #+#    #+#             */
/*   Updated: 2024/01/26 14:37:50 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	partition_array(char **envp, int start, int end)
{
	char	*pivot;

	pivot = envp[(start + end) / 2];
	while (start <= end)
	{
		while (ft_strncmp(envp[start], pivot, ft_strlen(envp[start])) < 0)
			start++;
		while (ft_strncmp(envp[end], pivot, ft_strlen(envp[end])) > 0)
			end--;
		if (start <= end)
		{
			ft_swap(&envp[start], &envp[end]);
			start++;
			end--;
		}
	}
	return (start);
}

void	sort_envp(char **envp, int start, int end)
{
	int	pivot;

	pivot = partition_array(envp, start, end);
	if (start < pivot - 1)
		sort_envp(envp, start, pivot - 1);
	if (end > pivot)
		sort_envp(envp, pivot, end);
}
