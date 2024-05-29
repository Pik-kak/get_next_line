/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:31:37 by kkauhane          #+#    #+#             */
/*   Updated: 2023/12/15 13:55:34 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*get_next(char *totalread)
{
	char	*newline;
	char	*pointer;
	int		length;

	pointer = ft_strchr(totalread, '\n');
	length = (pointer - totalread) + 1;
	newline = ft_substr(totalread, 0, length);
	if (!newline)
		return (NULL);
	return (newline);
}

char	*get_remainder(char *totalread)
{
	char	*remainder;
	char	*pointer;
	int		length;

	pointer = ft_strchr(totalread, '\n');
	if (!pointer)
	{
		remainder = NULL;
		return (ft_free(&totalread));
	}
	length = (pointer - totalread) + 1;
	if (!totalread[length])
		return (ft_free(&totalread));
	remainder = ft_substr(totalread, length, ft_strlen(totalread) - length);
	if (!remainder)
		return (ft_free(&totalread));
	ft_free(&totalread);
	return (remainder);
}

char	*read_next_line(int fd, char *totalread)
{
	int		i;
	char	*buffer;

	i = 1;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&totalread));
	buffer[0] = '\0';
	while (i > 0 && !ft_strchr(buffer, '\n'))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i > 0)
		{
			buffer[i] = '\0';
			totalread = ft_strjoin(totalread, buffer);
			if (!totalread)
				return (ft_free(&buffer));
		}
	}
	free(buffer);
	if (i == -1)
		return (ft_free(&totalread));
	return (totalread);
}

char	*get_next_line(int fd)
{
	char		*nextline;
	static char	*totalread[65534];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 65534)
		return (0);
	if ((totalread[fd] && !ft_strchr(totalread[fd], '\n')) || !totalread[fd])
		totalread[fd] = read_next_line(fd, totalread[fd]);
	if (!totalread[fd])
		return (0);
	nextline = get_next(totalread[fd]);
	if (!nextline)
		return (ft_free(&totalread[fd]));
	totalread[fd] = get_remainder(totalread[fd]);
	return (nextline);
}
