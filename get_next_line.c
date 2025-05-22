/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:19:28 by mhachem           #+#    #+#             */
/*   Updated: 2025/05/22 11:17:17 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*malloc_buf(char *buf)
{
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	return (buf);
}

static char	*read_and_join(int fd, char *stash, char *tmp)
{
	char	*buf;
	ssize_t	bytes_read;

	buf = NULL;
	buf = malloc_buf(buf);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		tmp = stash;
		stash = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(stash, '\n'))
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (!stash || bytes_read < 0)
		return (free(stash), NULL);
	return (stash);
}

static char	*extract_line(char **stash)
{
	char	*newline;
	char	*line;
	char	*tmp;
	int		len;

	newline = ft_strchr(*stash, '\n');
	if (!*stash || !newline)
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
	char		*tmp;

	tmp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = read_and_join(fd, stash, tmp);
	if (!stash || !*stash)
		return (free(stash), stash = NULL, NULL);
	result = extract_line(&stash);
	if (!result)
	{
		if (!stash[0])
			return (free(stash), stash = NULL, NULL);
		result = stash;
		stash = NULL;
	}
	return (result);
}
