/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquinoa <aquinoa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 18:00:54 by aquinoa           #+#    #+#             */
/*   Updated: 2021/01/21 17:19:37 by aquinoa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

char	*find_tail(char **line, char **tail)
{
	char	*n;

	n = NULL;
	if (*tail)
	{
		if ((n = ft_strchr(*tail, '\n')))
		{
			*n = '\0';
			*line = *tail;
			*tail = ft_strdup(++n);
		}
		else
		{
			*line = *tail;
			*tail = NULL;
		}
	}
	else
		*line = ft_strdup("");
	return (n);
}

int		read_file(int fd, char **line, char **tail)
{
	char	*buff;
	char	*n;
	int		end_of_buff;

	n = NULL;
	if (!(buff = (char*)malloc(BUFFER_SIZE + 1)))
		return (-1);
	while (!n && (end_of_buff = read(fd, buff, BUFFER_SIZE)))
	{
		if (end_of_buff == -1)
			return (-1);
		buff[end_of_buff] = '\0';
		if ((n = ft_strchr(buff, '\n')))
		{
			*n = '\0';
			if (!(*tail = ft_strdup(++n)))
				return (-1);
		}
		if (!(*line = ft_strjoin(*line, buff)))
			return (-1);
	}
	free(buff);
	return (end_of_buff);
}

int		get_next_line(int fd, char **line)
{
	static char		*tail;
	int				get;

	get = 0;
	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1 || !line)
		return (-1);
	if (!(find_tail(line, &tail)))
		get = read_file(fd, line, &tail);
	if (!get && !tail)
		return (0);
	if (get == -1)
		return (-1);
	return (1);
}
