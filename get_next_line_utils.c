/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgenova <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:43:09 by dgenova           #+#    #+#             */
/*   Updated: 2022/01/23 18:59:39 by dgenova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strchr(const char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
		if (s[i] == c)
			return (i + 1);
	return (0);
}

char	*ft_buffcat(char **buff1, char *buff2)
{
	size_t	dst_len;
	char	*dst;
	int		i;
	int		j;

	dst_len = ft_strlen(*buff1) + ft_strlen(buff2) + 1;
	dst = (char *)malloc(sizeof(char) * dst_len);
	if (dst == NULL)
	{
		return (NULL);
	}
	i = -1;
	j = -1;
	if ((*buff1) != NULL)
	{
		while ((*buff1)[++i] != '\0')
			dst[++j] = (*buff1)[i];
		free(*buff1);
	}
	i = -1;
	while (buff2[++i] != '\0')
		dst[++j] = buff2[i];
	dst[++j] = '\0';
	*buff1 = dst;
	return (dst);
}

char	*ft_read_buffer(const char *buff, int start, int len)
{
	char	*tmp;
	int		i;
	int		j;

	if (len <= 0)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (tmp == NULL)
		return (NULL);
	i = -1;
	j = start - 1;
	while (++j < (start + len))
		tmp[++i] = buff[j];
	tmp[++i] = '\0';
	return (tmp);
}

char	*fd_readline(int fd, t_list *node)
{
	char	*line;
	ssize_t	len;
	char	*tmp;

	tmp = node->b;
	line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (line == NULL)
		return (NULL);
	while (1)
	{
		len = read(fd, line, BUFFER_SIZE);
		if (len <= 0)
			break ;
		line[len] = '\0';
		tmp = ft_buffcat(&node->b, line);
		if (tmp == NULL)
			break ;
		if (ft_strchr(tmp, '\n'))
			break ;
	}
	free(line);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}
