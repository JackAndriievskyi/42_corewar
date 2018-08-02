/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleshche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 19:30:17 by oleshche          #+#    #+#             */
/*   Updated: 2017/12/21 14:50:57 by oleshche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			line_size(char *str)
{
	char *s;

	s = ft_strchr(str, '\n');
	if (s)
		return (s - str);
	else
		return (ft_strlen(str));
}

static t_list		*fill_list(int fd, t_list **files)
{
	t_list *curr;

	curr = *files;
	while (curr)
	{
		if (curr->content_size == (size_t)fd)
			return (curr);
		curr = curr->next;
	}
	if (!(curr = ft_lstnew("", fd)))
		return (NULL);
	ft_lstadd(files, curr);
	return (curr);
}

static int			fill_line(char **line, char **str)
{
	int size;

	size = line_size(*str);
	if (!(*line = ft_strnew(size)))
		return (0);
	ft_memcpy(*line, *str, size);
	if (ft_strchr(*str, '\n'))
		ft_memmove(*str, *str + size + 1, ft_strlen(*str + size + 1) + 1);
	else
		ft_strclr(*str);
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*files;
	t_list			*curr;
	char			*tmp;
	int				ret;
	char			buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || read(fd, buf, 0) == -1)
		return (-1);
	CHECKALLOC((curr = fill_list(fd, &files)));
	while ((ret = read(fd, buf, BUFF_SIZE)) && ret != -1)
	{
		buf[ret] = '\0';
		CHECKALLOC((tmp = ft_strjoin(curr->content, buf)));
		free(curr->content);
		curr->content = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ft_strlen(curr->content))
	{
		CHECKALLOC(fill_line(line, (char**)&curr->content));
		return (1);
	}
	return (0);
}
