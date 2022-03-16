/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuranus <zuranus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:59:30 by zuranus           #+#    #+#             */
/*   Updated: 2021/12/01 19:32:20 by zuranus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*ft_get_next_line_free(char *str_static)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (str_static[i] && str_static[i] != '\n')
		i++;
	if (!str_static[i])
	{
		free(str_static);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(str_static) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (str_static[i])
		str[j++] = str_static[i++];
	str[j] = '\0';
	free(str_static);
	return (str);
}

char	*ft_get_next_line_n(char *str_static)
{
	int		i;
	char	*str;

	i = 0;
	if (!str_static[i])
		return (NULL);
	while (str_static[i] && str_static[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (str_static[i] && str_static[i] != '\n')
	{
		str[i] = str_static[i];
		i++;
	}
	if (str_static[i] == '\n')
	{
		str[i] = str_static[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_get_next_line_read(int fd, char *str_static)
{
	char	*buff;
	int		null_bait;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	null_bait = 1;
	while (!ft_strchr(str_static, '\n') && null_bait != 0)
	{
		null_bait = read(fd, buff, BUFFER_SIZE);
		if (null_bait == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[null_bait] = '\0';
		str_static = ft_strjoin(str_static, buff);
	}
	free(buff);
	return (str_static);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*str_static;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str_static = ft_get_next_line_read(fd, str_static);
	if (!str_static)
		return (NULL);
	str = ft_get_next_line_n(str_static);
	str_static = ft_get_next_line_free(str_static);
	return (str);
}
