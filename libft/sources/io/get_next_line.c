/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:33:47 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:40:21 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static char	*get_line_from_stash(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*get_remaining_stash(char *stash)
{
	int		i;
	int		j;
	char	*remaining;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	remaining = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!remaining)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		remaining[j++] = stash[i++];
	remaining[j] = '\0';
	free(stash);
	return (remaining);
}

static char	*fd_to_stash(int fd, char *stash)
{
	char	*buff;
	int		rb;

	rb = 1;
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (!gnl_strchr(stash, '\n') && rb != 0)
	{
		rb = read(fd, buff, BUFFER_SIZE);
		if (rb == -1)
		{
			free(buff);
			free(stash);
			return (NULL);
		}
		buff[rb] = '\0';
		stash = gnl_strjoin(stash, buff);
	}
	free(buff);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (0);
	stash[fd] = fd_to_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = get_line_from_stash(stash[fd]);
	stash[fd] = get_remaining_stash(stash[fd]);
	return (line);
}
