/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflorea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:02:20 by aflorea           #+#    #+#             */
/*   Updated: 2025/12/21 14:43:51 by aflorea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	if (c == '\0')
	{
		while (s[i] != '\0')
			i++;
		return (i);
	}
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] == c)
		return (i + 1);
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	char	*s;
	size_t	i;
	size_t	total;

	if (!nmemb || !size)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	total = nmemb * size;
	p = malloc(total);
	if (!p)
		return (NULL);
	s = (char *)p;
	i = 0;
	while (i < total)
		s[i++] = '\0';
	return (p);
}

void	*ft_memmove(void *dest, const void *src, int n)
{
	char		*temp;
	const char	*s;

	if (!dest && !src)
		return (NULL);
	temp = (char *)dest;
	s = (const char *)src;
	if (temp <= s)
	{
		while (n--)
			*temp++ = *s++;
	}
	else
	{
		while (n--)
			temp[n] = s[n];
	}
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2, size_t len)
{
	char	*res;
	size_t	l1;
	size_t	l2;

	l1 = ft_strlen(s1, '\0');
	l2 = ft_strlen(s2, '\0');
	if (len < l2)
		l2 = len;
	res = (char *)ft_calloc(l1 + l2 + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_memmove(res, s1, (int)l1);
	ft_memmove(res + l1, s2, (int)l2);
	res[l1 + l2] = '\0';
	free(s1);
	return (res);
}
