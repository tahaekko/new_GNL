/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:19:19 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/04 12:21:50 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static char	*ft_read(char *readed, int fd)
{
	char	*buff;
	int		rdb;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	rdb = 1;
	while (rdb > 0 && !ft_isnewline(readed))
	{
		rdb = read(fd, buff, BUFFER_SIZE);
		buff[rdb] = '\0';
		readed = ft_gstrjoin(readed, buff);
		if (!readed)
			return (free(buff), NULL);
		if (!readed[0] && rdb == 0)
			return (free(readed), free(buff), NULL);
	}
	return (free(buff), readed);
}

char	*ft_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(line, str, i + 1);
	return (line);
}

static char	*ft_next(char *str)
{
	char	*next;
	size_t	len;
	size_t	j;

	if (!str)
		return (NULL);
	len = ft_linelen(str);
	next = (char *)malloc((ft_strlen(str) - len + 1) * sizeof(char));
	if (!next)
		return (free(str), NULL);
	len++;
	j = 0;
	while (str[len])
	{
		next[j] = str[len];
		len++;
		j++;
	}
	next[j] = '\0';
	free(str);
	return (next);
}

char	*gnl(int fd)
{
	static char	*readed;
	char		*line;

	readed = ft_read(readed, fd);
	line = ft_line(readed);
	readed = ft_next(readed);
	return (line);
}
