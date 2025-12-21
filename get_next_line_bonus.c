/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflorea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:02:02 by aflorea           #+#    #+#             */
/*   Updated: 2025/12/21 14:43:24 by aflorea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*on_read_end(char *buffo, char *res, int *flag, int bytes)
{
	if (bytes < 0)
	{
		free(buffo);
		free(res);
		return (NULL);
	}
	*flag = 1;
	free(buffo);
	return (res);
}

static char	*empty_cache(char	*cache, int	*flag)
{
	int		count;
	int		cache_len;
	char	*res;

	res = (char *)ft_calloc(1, 1);
	if (cache[0] != '\0')
	{
		count = ft_strlen(cache, '\n');
		if (cache[count - 1] == '\n')
			*flag = 1;
		res = ft_strjoin(res, cache, count);
		cache_len = ft_strlen(cache, '\0');
		ft_memmove(cache, &cache[count], cache_len - count);
		cache[cache_len - count] = '\0';
	}
	return (res);
}

static char	*buffer_read(char *cache, int fd, char *res, int *flag)
{
	int		bytes;
	int		count;
	char	*buffo;

	buffo = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes = read(fd, buffo, BUFFER_SIZE);
	if (bytes <= 0)
		return (on_read_end(buffo, res, flag, bytes));
	buffo[bytes] = '\0';
	count = ft_strlen(buffo, '\n');
	if (count > 0 && buffo[count - 1] == '\n')
		*flag = 1;
	ft_memmove(cache, buffo, bytes + 1);
	free(buffo);
	res = ft_strjoin(res, cache, count);
	ft_memmove(cache, &cache[count], bytes - count);
	cache[bytes - count] = '\0';
	return (res);
}

static char	*read_loop(char *cache, int fd)
{
	int		flag;
	char	*res;

	flag = 0;
	res = empty_cache(cache, &flag);
	while (!flag)
	{
		res = buffer_read(cache, fd, res, &flag);
		if (!res || res[0] == '\0')
			return (res);
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*cache[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE < 1)
		return (NULL);
	if (!cache[fd])
		cache[fd] = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	line = read_loop(cache[fd], fd);
	if (!line || line[0] == '\0')
	{
		free(line);
		free(cache[fd]);
		cache[fd] = NULL;
		return (NULL);
	}
	return (line);
}

// #include <sys/stat.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// int	main(void)
// {
// 	int fd1 = open("./test1.txt", O_RDONLY);
// 	int fd2 = open("./test3.txt", O_RDONLY);

// 	char *s1 = "ciao";
// 	char *s2 = "mondo";
// 	while (s1 || s2)
// 	{
// 		s1 = get_next_line(fd1);
// 		printf("%s", s1);
// 		free(s1);
// 		s2 = get_next_line(fd2);
// 		printf("%s", s2);
// 		free(s2);
// 	}
// 	return (0);
// }
