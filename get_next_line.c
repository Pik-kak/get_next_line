/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkauhane <kkauhane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:31:37 by kkauhane          #+#    #+#             */
/*   Updated: 2023/12/15 14:06:08 by kkauhane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*totalread;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if ((totalread && !ft_strchr(totalread, '\n')) || !totalread)
		totalread = read_next_line(fd, totalread);
	if (!totalread)
		return (0);
	nextline = get_next(totalread);
	if (!nextline)
		return (ft_free(&totalread));
	totalread = get_remainder(totalread);
	return (nextline);
}
