/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:19:28 by mhachem           #+#    #+#             */
/*   Updated: 2025/05/05 13:06:03 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_join(int fd, char *stash)
{
	char	*buf;
	char	*tmp;
	ssize_t	bytes_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read == BUFFER_SIZE)
	{
		buf[bytes_read] = '\0';
		tmp = stash;
		stash = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(stash, '\n'))
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes_read >= 0)
		buf[bytes_read] = '\0';
	free(buf);
	return (stash);
}

static char	*extract_line(char **stash)
{
	char	*newline;
	char	*line;
	char	*tmp;
	int		len;

	newline = ft_strchr(*stash, '\n');
	if (!newline)
		return (NULL);
	len = newline - *stash + 1;
	line = ft_substr(*stash, 0, len);
	tmp = *stash;
	*stash = ft_strdup(newline + 1);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = read_and_join(fd, stash);
	if (!stash || !*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	result = extract_line(&stash);
	if (!result)
	{
		result = ft_strdup(stash);
		free(stash);
		stash = NULL;
	}
	return (result);
}
