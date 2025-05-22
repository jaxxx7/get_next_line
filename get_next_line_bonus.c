/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:19:28 by mhachem           #+#    #+#             */
/*   Updated: 2025/05/22 12:55:09 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *malloc_buf(char *buf)
{
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	return (buf);
}

static char *read_and_join(int fd, char *stash, char *tmp)
{
	char *buf;
	ssize_t bytes_read;

	buf = NULL;
	buf = malloc_buf(buf);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		tmp = stash;
		stash = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(stash, '\n') || !stash || bytes_read < BUFFER_SIZE)
			break;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (!stash || bytes_read < 0)
		return (free(stash), NULL);
	return (stash);
}

static char *extract_line(char **stash)
{
	char *newline;
	char *line;
	char *tmp;
	int len;

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

char *get_next_line(int fd)
{
	static char *stash[MAX_FD];
	char *result;
	char *tmp;

	tmp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_strdup("");
	stash[fd] = read_and_join(fd, stash[fd], tmp);
	if (!stash[fd] || !*stash[fd])
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	result = extract_line(&stash[fd]);
	if (!result)
	{
		if (stash[fd][0] == '\0')
			return (free(stash[fd]), stash[fd] = NULL, NULL);
		result = stash[fd];
		stash[fd] = NULL;
	}
	return (result);
}
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

int main(void)
{
	int fd1, fd2;
	char *line1 = NULL;
	char *line2 = NULL;
	int read1 = 1;
	int read2 = 1;

	fd1 = open("test1.txt", O_RDONLY);
	if (fd1 < 0)
	{
		perror("Error opening test1.txt");
		return (1);
	}

	fd2 = open("test2.txt", O_RDONLY);
	if (fd2 < 0)
	{
		perror("Error opening test2.txt");
		close(fd1);
		return (1);
	}

	while (read1 || read2)
	{
		if (read1)
		{
			line1 = get_next_line(fd1);
			if (line1)
			{
				printf("test1.txt: %s", line1);
				free(line1);
			}
			else
				read1 = 0;
		}
		if (read2)
		{
			line2 = get_next_line(fd2);
			if (line2)
			{
				printf("test2.txt: %s", line2);
				free(line2);
			}
			else
				read2 = 0;
		}
	}

	close(fd1);
	close(fd2);
	return (0);
}
