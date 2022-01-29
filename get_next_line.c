/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgenova <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:43:09 by dgenova           #+#    #+#             */
/*   Updated: 2022/01/23 18:59:39 by dgenova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*get_fd_node(t_list **fd_list, int fd);
static t_list	*create_fd_node(int fd);
static t_list	*find_fd_node(t_list **fd_list, int fd);
static void		remove_fd_node(t_list **fd_list, int fd);

static t_list	*get_fd_node(t_list **fd_list, int fd)
{
	t_list	*node;

	if (fd < 0)
		return (NULL);
	if (*fd_list == NULL)
	{
		node = create_fd_node(fd);
		if (node == NULL)
			return (NULL);
		*fd_list = node;
		return (node);
	}
	node = find_fd_node(fd_list, fd);
	if (node != NULL)
		return (node);
	node = create_fd_node(fd);
	if (node == NULL)
		return (NULL);
	node->next = *fd_list;
	(node->next)->previous = node;
	(*fd_list) = node;
	return (node);
}

static t_list	*create_fd_node(int fd)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->fd = fd;
	node->b = NULL;
	node->line = NULL;
	node->previous = NULL;
	node->next = NULL;
	return (node);
}

static t_list	*find_fd_node(t_list **fd_list, int fd)
{
	t_list	*head;
	t_list	*node;

	head = *fd_list;
	while (*fd_list != NULL)
	{
		if ((*fd_list)->fd == fd)
		{
			node = (*fd_list);
			(*fd_list) = head;
			return (node);
		}
		(*fd_list) = (*fd_list)->next;
	}
	*fd_list = head;
	return (NULL);
}

static void	remove_fd_node(t_list **fd_list, int fd)
{
	t_list	*node;

	if (fd < 0)
		return ;
	node = find_fd_node(fd_list, fd);
	if (node == NULL)
		return ;
	if (node->previous == NULL && node->next != NULL)
		*fd_list = node->next;
	if (node->previous != NULL)
		(node->previous)->next = node->next;
	if (node->next != NULL)
		(node->next)->previous = node->previous;
	if (node->previous == NULL && node->next == NULL)
		*fd_list = NULL;
	if (node->b != NULL)
		free(node->b);
	if (node->line != NULL)
		free(node->line);
	free(node);
}

char	*get_next_line(int fd)
{
	static t_list	*fd_list;
	t_list			*node;
	char			*ptr;
	int				i;

	node = get_fd_node(&fd_list, fd);
	if (BUFFER_SIZE < 1 || node == NULL || fd_readline(fd, node) == NULL)
	{
		remove_fd_node(&fd_list, fd);
		return (NULL);
	}
	free(node->line);
	i = ft_strchr(node->b, '\n');
	if (i > 0)
	{
		node->line = ft_read_buffer(node->b, 0, i);
		ptr = node->b;
		node->b = ft_read_buffer(node->b, i, (int)ft_strlen(node->b) - i);
		free(ptr);
		return (ft_read_buffer(node->line, 0, (int)ft_strlen(node->line)));
	}
	node->line = node->b;
	node->b = NULL;
	return (ft_read_buffer(node->line, 0, (int)ft_strlen(node->line)));
}
