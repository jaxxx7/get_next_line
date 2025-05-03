/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:19:28 by mhachem           #+#    #+#             */
/*   Updated: 2025/05/03 14:49:16 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	static char	*stash;
	char		*buf;
	ssize_t		bytes_read;
	char		*result;
	int			len;
	char		*tmp;
	char		*newline;

	if (!stash)
		stash = ft_strdup("");
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while ((bytes_read = read(fd, buf, BUFFER_SIZE)) == BUFFER_SIZE)
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
		if (bytes_read == 0)
		{
			free(buf);
			return (NULL);
		}
		result = ft_strdup(stash);
		printf("la frerot t'es en bas et c'est %s\n", result);
		free(stash);
		stash = NULL;
		free(buf);
		return (result);
	}
}
