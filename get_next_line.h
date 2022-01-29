/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgenova <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:43:09 by dgenova           #+#    #+#             */
/*   Updated: 2022/01/23 18:59:39 by dgenova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list {
	int				fd;
	char			*b;
	char			*line;
	struct s_list	*next;
	struct s_list	*previous;
}	t_list;

char			*fd_readline(int fd, t_list *node);
char			*ft_buffcat(char **buff1, char *buff2);
size_t			ft_strlen(const char *s);
int				ft_strchr(const char *s, char c);
char			*ft_read_buffer(const char *buff, int start, int len);
char			*get_next_line(int fd);
#endif
