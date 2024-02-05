/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:17:42 by agan              #+#    #+#             */
/*   Updated: 2024/02/05 15:17:43 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int arg_checker(int argc, char **argv)
{
    if (argc > 1 && argv)
    {
        ft_putstr_fd("Minishell does not accept arguments.\n", 2);
        return (-1);
    }
    return (0);
}


