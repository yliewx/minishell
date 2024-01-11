/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:28:44 by yliew             #+#    #+#             */
/*   Updated: 2023/10/02 18:22:42 by yliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_free(char **target)
{
	if (*target)
	{
		free(*target);
		*target = NULL;
	}
}

static void	get_read_result(int fd, char **result, char *buffer)
{
	char	*temp_result;
	ssize_t	bytes_read;

	if (!*result)
		*result = ft_calloc(1, 1);
	if (*result)
	{
		bytes_read = 1;
		while (bytes_read > 0 && !(ft_strchr(buffer, '\n')))
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read == -1 || bytes_read < 0)
			{
				ft_free(result);
				break ;
			}
			buffer[bytes_read] = '\0';
			temp_result = *result;
			*result = ft_strjoin(temp_result, buffer);
			ft_free(&temp_result);
			if (!*result)
				break ;
		}
	}
	ft_free(&buffer);
}

static char	*parse_read_result(char **result)
{
	char	*temp;
	char	*line;
	size_t	i;

	i = 0;
	while ((*result)[i] && (*result)[i] != '\n')
		i++;
	line = ft_substr(*result, 0, i + 1);
	if (!line || !line[0])
	{
		ft_free(&line);
		if (!line)
			ft_free(result);
		return (NULL);
	}
	temp = *result;
	*result = ft_substr(temp, i + 1, ft_strlen(temp) - i - 1);
	ft_free(&temp);
	if (!*result || !*result[0])
	{
		ft_free(result);
		if (!result)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*result;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	get_read_result(fd, &result, buffer);
	if (!result)
	{
		ft_free(&result);
		return (NULL);
	}
	line = parse_read_result(&result);
	return (line);
}
/*
int	main(void)
{
	int	fd;
	char	*result = NULL;

	fd = open("../gnl_tests/test.txt", O_RDONLY);
	while ((result = get_next_line(fd)) != NULL)
	{
		printf("%s", result);
		free(result);
	}
	close(fd);
	return (0);
}
*/
