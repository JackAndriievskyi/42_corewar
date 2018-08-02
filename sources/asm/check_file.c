/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleshche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 13:40:08 by oleshche          #+#    #+#             */
/*   Updated: 2018/08/01 12:00:10 by yandriie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oleshche.h"

int			only_spaces(char *str)
{
	while (str && *str)
		if (!ft_isspace(*(str++)))
			return (0);
	return (1);
}

int			comment_line(char *line)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == COMMENT_CHAR)
		return (1);
	return (0);
}

char		**file_map(t_list **file_lst)
{
	char	**file;
	t_list	*tmp;
	int		size_lst;
	int		i;

	size_lst = lst_size(*file_lst);
	file = (char**)malloc(sizeof(char*) * (size_lst + 1));
	i = -1;
	tmp = *file_lst;
	while (++i < size_lst)
	{
		file[i] = ft_strdup((char*)tmp->content);
		tmp = tmp->next;
	}
	file[i] = NULL;
	ft_lstdel(file_lst, &del_line);
	return (file);
}

int			labels(char **file)
{
	int		i;

	i = skip_start(file);
	parse_labels(file, i);
	return (check_code());
}

int			check_this_out(int fd)
{
	t_list	*file_lst;
	char	**file;
	char	*line;

	file_lst = NULL;
	while (get_next_line(fd, &line))
	{
		ft_lstaddback(&file_lst, ft_lstnew(line, ft_strlen(line) + 1));
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (!file_lst)
		return (print_err_msg(SYNTAX_ERR, 0, 0));
	file = file_map(&file_lst);
	if (name_check(file) || comment_check(file) || labels(file))
	{
		del_str_arr(file);
		return (1);
	}
	del_str_arr(file);
	return (NO_ERR);
}
