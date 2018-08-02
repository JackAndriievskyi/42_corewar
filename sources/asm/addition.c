/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleshche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 18:35:45 by oleshche          #+#    #+#             */
/*   Updated: 2018/07/01 18:35:47 by oleshche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oleshche.h"

static void	del_cmd_lst(void *cmd_lst, size_t size)
{
	t_command	*tmp;
	int			j;

	size = 0;
	tmp = (t_command*)cmd_lst;
	j = -1;
	while (++j < 3)
		if (tmp->args[j])
			ft_strdel(&tmp->args[j]);
	ft_strdel(&tmp->cmd_name);
	free(cmd_lst);
}

void		del_label(void *label, size_t size)
{
	t_label	*elem;

	size = 0;
	elem = (t_label*)label;
	ft_lstdel(&elem->commands, &del_cmd_lst);
	ft_strdel(&elem->label);
	free(label);
}

void		del_line(void *str, size_t size)
{
	ft_memset(str, 0, size);
	free(str);
}

int			lst_size(t_list *begin_lst)
{
	int	counter;

	counter = 0;
	while (begin_lst)
	{
		counter++;
		begin_lst = begin_lst->next;
	}
	return (counter);
}

void		del_str_arr(char **file)
{
	int	i;

	i = -1;
	if (!file)
		return ;
	while (file[++i])
	{
		ft_memset(file[i], 0, ft_strlen(file[i]));
		ft_strdel(&(file[i]));
	}
	free(file);
}
