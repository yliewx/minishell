/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:18:08 by agan              #+#    #+#             */
/*   Updated: 2024/01/11 19:18:09 by agan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ft_strcmp(char *sep, char *str)
// {
//     int i;

//     i = 0;
//     while (sep[i] && str[i])
//     {
//         if (sep[i] != str[i])
//             return (sep[i] - str[i]);
//         i++;
//     }
//     return (sep[i] - str[i]);
// }

// int skip_spaces(int i, char *line)
// {
//     while (line[i] && line[i] == ' ')
//         i++;
//     return (i);
// }

// t_token *ft_lexer(char *line)
// {
//     t_token *token_list;
//     int i;

//     i = 0;
//     while (line[i])
//     {
//         i = skip_spaces(i, line);
//         // If line[i] == symbol
//         // Else, run string function
//     }
// }