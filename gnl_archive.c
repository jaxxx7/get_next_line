/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:35:02 by mhachem           #+#    #+#             */
/*   Updated: 2025/05/05 12:40:28 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buf;
	ssize_t		bytes_read;
	char		*result;
	int			len;
	char		*tmp;
	char		*newline;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
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
		newline = ft_strchr(stash, '\n');
		if (newline)
		{
			len = newline - stash + 1;
			result = ft_substr(stash, 0, len);
			stash = ft_strdup(newline + 1);
			free(buf);
			return (result);
		}
	}
	if (bytes_read < BUFFER_SIZE)
	{
		if (bytes_read <= 0)
		{
			free(buf);
			if (stash && *stash)
			{
				result = stash;
				stash = NULL;
				return (result);
			}
			free(stash);
			stash = NULL;
			return (NULL);
		}
		buf[bytes_read + 1] = '\0';
		tmp = stash;
		stash = ft_strjoin(tmp, buf);
		free(tmp);
		result = ft_strdup(stash);
		free(stash);
		stash = NULL;
		free(buf);
		return (result);
	}
	return (NULL);
}